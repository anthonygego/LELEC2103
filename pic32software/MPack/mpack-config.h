/**
 * This is a sample MPack configuration file. Copy it to mpack-config.h somewhere
 * in your project's include tree and, optionally, edit it to suit your setup.
 * In most cases you can leave this file with the default config.
 */

#ifndef MPACK_CONFIG_H
#define MPACK_CONFIG_H 1


/*
 * Features
 */

/** Enables compilation of the base Tag Reader. */
#define MPACK_READER 1

/** Enables compilation of the static Expect API. */
#define MPACK_EXPECT 1

/** Enables compilation of the dynamic Node API. */
#define MPACK_NODE 1

/** Enables compilation of the Writer. */
#define MPACK_WRITER 1


/*
 * Dependencies
 */

/**
 * Enables the use of C stdlib. This allows the library to use malloc
 * for debugging and in allocation helpers.
 */
#define MPACK_STDLIB 1

/**
 * Enables the use of C stdio. This adds helpers for easily
 * reading/writing C files and makes debugging easier.
 */
#define MPACK_STDIO 1

/**
 * Enables the setjmp()/longjmp() error handling option. Note that
 * you don't have to use it; this just enables the option. It can be
 * disabled to avoid the dependency on setjmp.h .
 */
#define MPACK_SETJMP 1

/**
 * \def MPACK_MALLOC
 *
 * Defines the memory allocation function used by mpack. This is used by
 * helpers for automatically allocating data the correct size, and for
 * debugging functions. If this macro is undefined, the allocation helpers
 * will not be compiled.
 *
 * A memory allocator is required for the Node API.
 */
#if defined(MPACK_STDLIB) && !defined(MPACK_MALLOC)
#define MPACK_MALLOC malloc
#endif

/**
 * \def MPACK_FREE
 *
 * Defines the memory free function used by mpack. This is used by helpers
 * for automatically allocating data the correct size. If this macro is
 * undefined, the allocation helpers will not be compiled.
 *
 * A memory allocator is required for the Node API.
 */
#if defined(MPACK_STDLIB) && !defined(MPACK_FREE)
#define MPACK_FREE free
#endif


/*
 * Debugging options
 */

/**
 * \def MPACK_DEBUG
 *
 * Enables debug features. You may want to wrap this around your
 * own debug preprocs; by default it uses NDEBUG.
 */
#ifdef NDEBUG
#define MPACK_DEBUG 0
#else
#define MPACK_DEBUG 1
#endif

/**
 * Set this to 1 to implement a custom mpack_assert_fail() function. This
 * function should take a const char* parameter containing the error message.
 *
 * Asserts are only used when MPACK_DEBUG is enabled, and can be triggered
 * by bugs in mpack or bugs due to incorrect usage of mpack.
 */
#define MPACK_CUSTOM_ASSERT 0

/**
 * \def MPACK_TRACKING
 *
 * Enables compound type size tracking in debug mode.
 * This ensures that the correct number of elements or bytes are written
 * or read.
 */
#if MPACK_DEBUG && defined(MPACK_MALLOC) && defined(MPACK_FREE)
#define MPACK_TRACKING 1
#endif


/*
 * Miscellaneous
 */

/**
 * Stack space to use when initializing a reader or writer with a
 * stack-allocated buffer.
 */
#define MPACK_STACK_SIZE 4096

/**
 * Starting size of node children array. Nodes with more children than
 * this will use a growable array during parsing for better security.
 */
#define MPACK_NODE_ARRAY_STARTING_SIZE 32

/**
 * The nesting limit for array/map nodes to prevent stack overflows and
 * out-of-memory situations from malicious data. I can't imagine real-world
 * data nesting more than this, but if yours does, please tell me about it!
 */
#define MPACK_NODE_MAX_DEPTH 2048


#endif