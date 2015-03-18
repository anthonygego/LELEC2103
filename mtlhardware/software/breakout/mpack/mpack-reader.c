/*
 * Copyright (c) 2015 Nicholas Fraser
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mpack-reader.h"

#if MPACK_READER

#if MPACK_TRACKING
struct mpack_reader_track_t {
    struct mpack_reader_track_t* next;
    mpack_type_t type;
    uint64_t count;
};
#endif

static void mpack_reader_add_track(mpack_reader_t* reader, mpack_type_t type, uint64_t count) {
    MPACK_UNUSED(reader);
    MPACK_UNUSED(type);
    MPACK_UNUSED(count);

    #if MPACK_TRACKING
    mpack_reader_track_t* track = (mpack_reader_track_t*) MPACK_MALLOC(sizeof(mpack_reader_track_t));
    if (!track) {
        mpack_reader_flag_error(reader, mpack_error_memory);
        return;
    }

    // map count is the number of key/value pairs
    if (type == mpack_type_map)
        count *= 2;

    track->next = reader->track;
    track->type = type;
    track->count = count;
    reader->track = track;
    #endif
}

#if MPACK_TRACKING
static void mpack_done_track(mpack_reader_t* reader, mpack_type_t type) {
    if (reader->error != mpack_ok)
        return;

    if (!reader->track) {
        mpack_assert(0, "attempting to close a %s but nothing was opened!", mpack_type_to_string(type));
        mpack_reader_flag_error(reader, mpack_error_bug);
        return;
    }

    if (reader->track->type != type) {
        mpack_assert(0, "attempting to close a %s but the open element is a %s!",
                mpack_type_to_string(type), mpack_type_to_string(reader->track->type));
        mpack_reader_flag_error(reader, mpack_error_bug);
        return;
    }

    if (reader->track->count != 0) {
        mpack_assert(0, "attempting to close a %s but there are %"PRIu64" left",
                mpack_type_to_string(type), reader->track->count);
        mpack_reader_flag_error(reader, mpack_error_bug);
        return;
    }

    mpack_reader_track_t* track = reader->track;
    reader->track = track->next;
    MPACK_FREE(track);
}

void mpack_track_read(mpack_reader_t* reader, bool bytes, uint64_t count) {
    if (reader->error != mpack_ok)
        return;

    if (reader->track) {

        // make sure it's the right type
        if (bytes) {
            if (reader->track->type == mpack_type_map || reader->track->type == mpack_type_array) {
                mpack_assert(0, "bytes bytes cannot be read within an %s", mpack_type_to_string(reader->track->type));
                mpack_reader_flag_error(reader, mpack_error_bug);
            }
        } else {
            if (reader->track->type != mpack_type_map && reader->track->type != mpack_type_array) {
                mpack_assert(0, "elements cannot be read within an %s", mpack_type_to_string(reader->track->type));
                mpack_reader_flag_error(reader, mpack_error_bug);
            }
        }

        // make sure we don't overflow
        if (reader->track->count < count) {
            mpack_assert(0, "too many elements/bytes read for %s", mpack_type_to_string(reader->track->type));
            mpack_reader_flag_error(reader, mpack_error_bug);
        }
        reader->track->count -= count;

    }
}
#endif

mpack_error_t mpack_reader_destroy_cancel(mpack_reader_t* reader) {
    return reader->error;
}

mpack_error_t mpack_reader_destroy(mpack_reader_t* reader) {
    #if MPACK_TRACKING
    if (reader->error == mpack_ok && reader->track) {
        mpack_assert(0, "reader has an unclosed %s", mpack_type_to_string(reader->track->type));
        mpack_reader_flag_error(reader, mpack_error_bug);
    }
    #endif
    return mpack_reader_destroy_cancel(reader);
}

size_t mpack_reader_remaining(mpack_reader_t* reader, const char** data) {
    #if MPACK_TRACKING
    if (reader->track) {
        mpack_assert(0, "reader has an unclosed %s", mpack_type_to_string(reader->track->type));
        mpack_reader_flag_error(reader, mpack_error_bug);
    }
    #endif
    if (data)
        *data = reader->buffer + reader->pos;
    return reader->left;
}

void mpack_reader_flag_error(mpack_reader_t* reader, mpack_error_t error) {
    mpack_log("reader %p setting error %i: %s\n", reader, (int)error, mpack_error_to_string(error));

    #if MPACK_TRACKING
    while (reader->track) {
        mpack_reader_track_t* track = reader->track;
        reader->track = track->next;
        MPACK_FREE(track);
    }
    #endif

    if (!reader->error) {
        reader->error = error;
        if (reader->jump)
            longjmp(reader->jump_env, 1);
    }
}

// A helper to call the reader fill function. This makes sure it's
// implemented and guards against overflow in case it returns -1.
static inline size_t mpack_fill(mpack_reader_t* reader, char* p, size_t count) {
    if (!reader->fill)
        return 0;
    size_t ret = reader->fill(reader->context, p, count);
    if (ret == ((size_t)(-1)))
        return 0;
    return ret;
}

// Reads count bytes into p. Used when there are not enough bytes
// left in the buffer to satisfy a read.
static void mpack_read_native_big(mpack_reader_t* reader, char* p, size_t count) {
    if (reader->error != mpack_ok)
        return;

    mpack_log("big read for %i bytes into %p, %i left in buffer, buffer size %i\n",
            (int)count, p, (int)reader->left, (int)reader->size);

    if (count <= reader->left) {
        mpack_assert(0,
                "big read requested for %i bytes, but there are %i bytes "
                "left in buffer. call mpack_read_native() instead",
                (int)count, (int)reader->left);
        mpack_reader_flag_error(reader, mpack_error_bug);
        return;
    }

    if (reader->size == 0) {
        // somewhat debatable what error should be returned here. when
        // initializing a reader with an in-memory buffer it's not
        // necessarily a bug if the data is blank; it might just have
        // been truncated to zero. for this reason we return the same
        // error as if the data was truncated.
        mpack_reader_flag_error(reader, mpack_error_io);
        return;
    }

    // flush what's left of the buffer
    if (reader->left > 0) {
        mpack_log("flushing %i bytes remaining in buffer\n", (int)reader->left);
        memcpy(p, reader->buffer + reader->pos, reader->left);
        count -= reader->left;
        p += reader->left;
        reader->pos += reader->left;
        reader->left = 0;
    }

    // we read only in multiples of the buffer size. read the middle portion, if any
    size_t middle = count - (count % reader->size);
    if (middle > 0) {
        mpack_log("reading %i bytes in middle\n", (int)middle);
        if (mpack_fill(reader, p, middle) < middle) {
            mpack_reader_flag_error(reader, mpack_error_io);
            return;
        }
        count -= middle;
        p += middle;
        if (count == 0)
            return;
    }

    // fill the buffer
    reader->pos = 0;
    reader->left = mpack_fill(reader, reader->buffer, reader->size);
    mpack_log("filled %i bytes into buffer\n", (int)reader->left);
    if (reader->left < count) {
        mpack_reader_flag_error(reader, mpack_error_io);
        return;
    }

    // serve the remainder
    mpack_log("serving %i remaining bytes from %p to %p\n", (int)count, reader->buffer+reader->pos,p);
    memcpy(p, reader->buffer + reader->pos, count);
    reader->pos += count;
    reader->left -= count;
}

void mpack_skip_bytes(mpack_reader_t* reader, size_t count) {
    char c[128];
    size_t i = 0;
    while (i < count && mpack_reader_error(reader) == mpack_ok) {
        size_t amount = ((count - i) > sizeof(c)) ? sizeof(c) : (count - i);
        mpack_read_bytes(reader, c, amount);
        i += amount;
    }
}

// Reads count bytes into p, deferring to mpack_read_native_big() if more
// bytes are needed than are available in the buffer.
void mpack_read_native(mpack_reader_t* reader, char* p, size_t count) {
    if (count > reader->left) {
        mpack_read_native_big(reader, p, count);
    } else {
        memcpy(p, reader->buffer + reader->pos, count);
        reader->pos += count;
        reader->left -= count;
    }
}

// Reads native bytes with jump disabled. This allows mpack reader functions
// to hold an allocated buffer and read native data into it without leaking it.
void mpack_read_native_nojump(mpack_reader_t* reader, char* p, size_t count) {
    #if MPACK_SETJMP
    bool jump = reader->jump;
    reader->jump = false;
    #endif
    mpack_read_native(reader, p, count);
    #if MPACK_SETJMP
    reader->jump = jump;
    #endif
}

void mpack_read_bytes(mpack_reader_t* reader, char* p, size_t count) {
    mpack_track_bytes_read(reader, count);
    mpack_read_native(reader, p, count);
}

const char* mpack_read_bytes_inplace(mpack_reader_t* reader, size_t count) {
    if (reader->error != mpack_ok)
        return NULL;

    if (count > reader->size) {
        mpack_reader_flag_error(reader, mpack_error_too_big);
        return NULL;
    }

    mpack_track_bytes_read(reader, count);

    // if we have enough bytes already in the buffer, we can return it directly.
    if (reader->left >= count) {
        reader->pos += count;
        reader->left -= count;
        return reader->buffer + reader->pos - count;
    }

    // we'll need a fill function to get more data
    if (!reader->fill) {
        mpack_reader_flag_error(reader, mpack_error_io);
        return NULL;
    }

    // shift the remaining data back to the start and fill the buffer back up
    memmove(reader->buffer, reader->buffer + reader->pos, reader->left);
    reader->pos = 0;
    reader->left += mpack_fill(reader, reader->buffer + reader->left, reader->size - reader->left);
    if (reader->left < count) {
        mpack_reader_flag_error(reader, mpack_error_io);
        return NULL;
    }
    return reader->buffer;
}

static uint16_t mpack_read_native_u16(mpack_reader_t* reader) {
    char c[sizeof(uint16_t)];
    mpack_read_native(reader, c, sizeof(c));
    return (((uint16_t)(uint8_t)c[0]) << 8) +
           ((uint16_t)(uint8_t)c[1]);
}

static uint32_t mpack_read_native_u32(mpack_reader_t* reader) {
    char c[sizeof(uint32_t)];
    mpack_read_native(reader, c, sizeof(c));
    return (((uint32_t)(uint8_t)c[0]) << 24) +
           (((uint32_t)(uint8_t)c[1]) << 16) +
           (((uint32_t)(uint8_t)c[2]) <<  8) +
           ((uint32_t)(uint8_t)c[3]);
}

static uint64_t mpack_read_native_u64(mpack_reader_t* reader) {
    char c[sizeof(uint64_t)];
    mpack_read_native(reader, c, sizeof(c));
    return (((uint64_t)(uint8_t)c[0]) << 56) +
           (((uint64_t)(uint8_t)c[1]) << 48) +
           (((uint64_t)(uint8_t)c[2]) << 40) +
           (((uint64_t)(uint8_t)c[3]) << 32) +
           (((uint64_t)(uint8_t)c[4]) << 24) +
           (((uint64_t)(uint8_t)c[5]) << 16) +
           (((uint64_t)(uint8_t)c[6]) <<  8) +
           ((uint64_t)(uint8_t)c[7]);
}

static inline int8_t  mpack_read_native_i8  (mpack_reader_t* reader) {return (int8_t) mpack_read_native_u8  (reader);}
static inline int16_t mpack_read_native_i16 (mpack_reader_t* reader) {return (int16_t)mpack_read_native_u16 (reader);}
static inline int32_t mpack_read_native_i32 (mpack_reader_t* reader) {return (int32_t)mpack_read_native_u32 (reader);}
static inline int64_t mpack_read_native_i64 (mpack_reader_t* reader) {return (int64_t)mpack_read_native_u64 (reader);}
static inline bool    mpack_read_native_bool(mpack_reader_t* reader) {return (bool)   mpack_read_native_u8  (reader);}

float mpack_read_native_float(mpack_reader_t* reader) {
    union {
        float f;
        uint32_t i;
    } u;
    u.i = mpack_read_native_u32(reader);
    return u.f;
}

double mpack_read_native_double(mpack_reader_t* reader) {
    union {
        double d;
        uint64_t i;
    } u;
    u.i = mpack_read_native_u64(reader);
    return u.d;
}

mpack_tag_t mpack_read_tag(mpack_reader_t* reader) {
    mpack_tag_t var;
    memset(&var, 0, sizeof(var));
    var.type = mpack_type_nil;

    // get the type
    uint8_t type = mpack_read_native_u8(reader);
    if (mpack_reader_error(reader))
        return var;
    mpack_track_element_read(reader);

    // look at the top 4 bits first to handle infix types
    switch (type >> 4) {

        // positive fixnum
        case 0x0: case 0x1: case 0x2: case 0x3:
        case 0x4: case 0x5: case 0x6: case 0x7:
            var.type = mpack_type_uint;
            var.v.i = type;
            return var;

        // negative fixnum
        case 0xe: case 0xf:
            var.type = mpack_type_int;
            var.v.i = (int32_t)(int8_t)type;
            return var;

        // fixmap
        case 0x8:
            var.type = mpack_type_map;
            var.v.u = type & ~0xf0;
            mpack_reader_add_track(reader, mpack_type_map, var.v.u);
            return var;

        // fixarray
        case 0x9:
            var.type = mpack_type_array;
            var.v.u = type & ~0xf0;
            mpack_reader_add_track(reader, mpack_type_array, var.v.u);
            return var;

        // fixstr
        case 0xa: case 0xb:
            var.type = mpack_type_str;
            var.v.u = type & ~0xe0;
            mpack_reader_add_track(reader, mpack_type_str, var.v.u);
            return var;

        // not an infix type
        default:
            break;

    }

    // handle individual types
    switch (type) {

        // nil
        case 0xc0:
            var.type = mpack_type_nil;
            return var;

        // bool
        case 0xc2: case 0xc3:
            var.type = mpack_type_bool;
            var.v.b = type & 1;
            return var;

        // bin8
        case 0xc4:
            var.type = mpack_type_bin;
            var.v.u = mpack_read_native_u8(reader);
            mpack_reader_add_track(reader, mpack_type_bin, var.v.u);
            return var;

        // bin16
        case 0xc5:
            var.type = mpack_type_bin;
            var.v.u = mpack_read_native_u16(reader);
            mpack_reader_add_track(reader, mpack_type_bin, var.v.u);
            return var;

        // bin32
        case 0xc6:
            var.type = mpack_type_bin;
            var.v.u = mpack_read_native_u32(reader);
            mpack_reader_add_track(reader, mpack_type_bin, var.v.u);
            return var;

        // ext8
        case 0xc7:
            var.type = mpack_type_ext;
            var.v.u = mpack_read_native_u8(reader);
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // ext16
        case 0xc8:
            var.type = mpack_type_ext;
            var.v.u = mpack_read_native_u16(reader);
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // ext32
        case 0xc9:
            var.type = mpack_type_ext;
            var.v.u = mpack_read_native_u32(reader);
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // float
        case 0xca:
            var.type = mpack_type_float;
            var.v.f = mpack_read_native_float(reader);
            return var;

        // double
        case 0xcb:
            var.type = mpack_type_double;
            var.v.d = mpack_read_native_double(reader);
            return var;

        // uint8
        case 0xcc:
            var.type = mpack_type_uint;
            var.v.u = mpack_read_native_u8(reader);
            return var;

        // uint16
        case 0xcd:
            var.type = mpack_type_uint;
            var.v.u = mpack_read_native_u16(reader);
            return var;

        // uint32
        case 0xce:
            var.type = mpack_type_uint;
            var.v.u = mpack_read_native_u32(reader);
            return var;

        // uint64
        case 0xcf:
            var.type = mpack_type_uint;
            var.v.u = mpack_read_native_u64(reader);
            return var;

        // int8
        case 0xd0:
            var.type = mpack_type_int;
            var.v.i = mpack_read_native_i8(reader);
            return var;

        // int16
        case 0xd1:
            var.type = mpack_type_int;
            var.v.i = mpack_read_native_i16(reader);
            return var;

        // int32
        case 0xd2:
            var.type = mpack_type_int;
            var.v.i = mpack_read_native_i32(reader);
            return var;

        // int64
        case 0xd3:
            var.type = mpack_type_int;
            var.v.i = mpack_read_native_i64(reader);
            return var;

        // fixext1
        case 0xd4:
            var.type = mpack_type_ext;
            var.v.u = 1;
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // fixext2
        case 0xd5:
            var.type = mpack_type_ext;
            var.v.u = 2;
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // fixext4
        case 0xd6:
            var.type = mpack_type_ext;
            var.v.u = 4;
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // fixext8
        case 0xd7:
            var.type = mpack_type_ext;
            var.v.u = 8;
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // fixext16
        case 0xd8:
            var.type = mpack_type_ext;
            var.v.u = 16;
            var.exttype = mpack_read_native_i8(reader);
            mpack_reader_add_track(reader, mpack_type_ext, var.v.u);
            return var;

        // str8
        case 0xd9:
            var.type = mpack_type_str;
            var.v.u = mpack_read_native_u8(reader);
            mpack_reader_add_track(reader, mpack_type_str, var.v.u);
            return var;

        // str16
        case 0xda:
            var.type = mpack_type_str;
            var.v.u = mpack_read_native_u16(reader);
            mpack_reader_add_track(reader, mpack_type_str, var.v.u);
            return var;

        // str32
        case 0xdb:
            var.type = mpack_type_str;
            var.v.u = mpack_read_native_u32(reader);
            mpack_reader_add_track(reader, mpack_type_str, var.v.u);
            return var;

        // array16
        case 0xdc:
            var.type = mpack_type_array;
            var.v.u = mpack_read_native_u16(reader);
            mpack_reader_add_track(reader, mpack_type_array, var.v.u);
            return var;

        // array32
        case 0xdd:
            var.type = mpack_type_array;
            var.v.u = mpack_read_native_u32(reader);
            mpack_reader_add_track(reader, mpack_type_array, var.v.u);
            return var;

        // map16
        case 0xde:
            var.type = mpack_type_map;
            var.v.u = mpack_read_native_u16(reader);
            mpack_reader_add_track(reader, mpack_type_map, var.v.u);
            return var;

        // map32
        case 0xdf:
            var.type = mpack_type_map;
            var.v.u = mpack_read_native_u32(reader);
            mpack_reader_add_track(reader, mpack_type_map, var.v.u);
            return var;

        // reserved (only 0xc1 should be left)
        default:
            break;
    }

    // unrecognized type
    mpack_reader_flag_error(reader, mpack_error_invalid);
    return var;
}

void mpack_discard(mpack_reader_t* reader) {
    mpack_tag_t var = mpack_read_tag(reader);
    if (mpack_reader_error(reader))
        return;
    switch (var.type) {
        case mpack_type_str:
            mpack_skip_bytes(reader, var.v.u);
            mpack_done_str(reader);
            break;
        case mpack_type_bin:
            mpack_skip_bytes(reader, var.v.u);
            mpack_done_bin(reader);
            break;
        case mpack_type_ext:
            mpack_skip_bytes(reader, var.v.u);
            mpack_done_ext(reader);
            break;
        case mpack_type_array: {
            for (; var.v.u > 0; --var.v.u) {
                mpack_discard(reader);
                if (mpack_reader_error(reader))
                    break;
            }
            break;
        }
        case mpack_type_map: {
            for (; var.v.u > 0; --var.v.u) {
                mpack_discard(reader);
                mpack_discard(reader);
                if (mpack_reader_error(reader))
                    break;
            }
            break;
        }
        default:
            break;
    }
}

#if MPACK_TRACKING
void mpack_done_array(mpack_reader_t* reader) {
    mpack_done_track(reader, mpack_type_array);
}

void mpack_done_map(mpack_reader_t* reader) {
    mpack_done_track(reader, mpack_type_map);
}

void mpack_done_str(mpack_reader_t* reader) {
    mpack_done_track(reader, mpack_type_str);
}

void mpack_done_bin(mpack_reader_t* reader) {
    mpack_done_track(reader, mpack_type_bin);
}

void mpack_done_ext(mpack_reader_t* reader) {
    mpack_done_track(reader, mpack_type_ext);
}
#endif

#if MPACK_STDIO
size_t mpack_fread(void* context, char* buffer, size_t count) {
    return fread((void*)buffer, 1, count, (FILE*)context);
}
#endif

#if MPACK_DEBUG && MPACK_STDIO && MPACK_SETJMP
static void mpack_debug_print_element(mpack_reader_t* reader, size_t depth) {
    mpack_tag_t val = mpack_read_tag(reader);
    size_t i;
    switch (val.type) {

        case mpack_type_nil:
            printf("null");
            break;
        case mpack_type_bool:
            printf(val.v.b ? "true" : "false");
            break;

        case mpack_type_float:
            printf("%f", val.v.f);
            break;
        case mpack_type_double:
            printf("%f", val.v.d);
            break;

        case mpack_type_int:
            printf("%"PRIi64, val.v.i);
            break;
        case mpack_type_uint:
            printf("%"PRIu64, val.v.u);
            break;

        case mpack_type_bin:
            // skip data
            for(i=0; i < val.v.u; ++i)
                mpack_read_native_u8(reader);
            printf("<binary data>");
            mpack_done_bin(reader);
            break;

        case mpack_type_ext:
            // skip data
            for(i=0; i < val.v.u; ++i)
                mpack_read_native_u8(reader);
            printf("<ext data of type %i>", val.exttype);
            mpack_done_ext(reader);
            break;

        case mpack_type_str:
            putchar('"');
            for(i=0; i < val.v.u; ++i) {
                char c;
                mpack_read_bytes(reader, &c, 1);
                switch (c) {
                    case '\n': printf("\\n"); break;
                    case '\\': printf("\\\\"); break;
                    case '"': printf("\\\""); break;
                    default: putchar(c); break;
                }
            }
            putchar('"');
            mpack_done_str(reader);
            break;

        case mpack_type_array:
            printf("[\n");
            for(i=0; i < val.v.u; ++i) {
                size_t j;
                for(j=0; j < depth + 1; ++j)
                    printf("    ");
                mpack_debug_print_element(reader, depth + 1);
                if (i != val.v.u - 1)
                    putchar(',');
                putchar('\n');
            }
            size_t i; for(i=0; i < depth; ++i)
                printf("    ");
            putchar(']');
            mpack_done_array(reader);
            break;

        case mpack_type_map:
            printf("{\n");
            for(i=0; i < val.v.u; ++i) {
                size_t j;
                for(j=0; j < depth + 1; ++j)
                    printf("    ");
                mpack_debug_print_element(reader, depth + 1);
                printf(": ");
                mpack_debug_print_element(reader, depth + 1);
                if (i != val.v.u - 1)
                    putchar(',');
                putchar('\n');
            }
            for(i=0; i < depth; ++i)
                printf("    ");
            putchar('}');
            mpack_done_map(reader);
            break;
    }
}

void mpack_debug_print(const char* data, int len) {
    mpack_reader_t reader;
    mpack_reader_init_buffer(&reader, data, len);
    if (MPACK_READER_SETJMP(&reader)) {
        printf("<mpack parsing error %s>\n", mpack_error_to_string(mpack_reader_error(&reader)));
        return;
    }

    int depth = 2;
    int i; for(i=0; i < depth; ++i)
        printf("    ");
    mpack_debug_print_element(&reader, depth);
    putchar('\n');

    if (mpack_reader_remaining(&reader, NULL) > 0)
        printf("<%i extra bytes at end of mpack>\n", (int)mpack_reader_remaining(&reader, NULL));
}
#endif

#endif

