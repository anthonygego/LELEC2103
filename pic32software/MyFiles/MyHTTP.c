/*********************************************************************
 *
 *  Application to Demo HTTP2 Server
 *  Support for HTTP2 module in Microchip TCP/IP Stack
 *	 -Implements the application 
 *	 -Reference: RFC 1002
 *
 ********************************************************************/
#define MyHTTP

#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "TCPIPStack/TCPIP.h"
#include "MyApp.h"
#include "mpack.h"

#define LED0_IO     (LATBbits.LATB9)
#define LED1_IO     (LATBbits.LATB9)
#define LED2_IO     (LATBbits.LATB9)
#define LED3_IO     (LATBbits.LATB9)
#define LED4_IO     (LATBbits.LATB10)
#define LED5_IO     (LATBbits.LATB10)
#define LED6_IO     (LATBbits.LATB10)
#define LED7_IO     (LATBbits.LATB10)

#define BUTTON0_IO  (LATBbits.LATB9)
#define BUTTON1_IO  (LATBbits.LATB9)
#define BUTTON2_IO  (LATBbits.LATB10)
#define BUTTON3_IO  (LATBbits.LATB10)

/****************************************************************************
  Section:
	Function Prototypes and Memory Globalizers
  ***************************************************************************/
#if defined(HTTP_USE_POST)
        static HTTP_IO_RESULT HTTPPostGame(void);
#endif

// RAM allocated for DDNS parameters
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	static BYTE DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
static BOOL lastFailure = FALSE;

/****************************************************************************
  Section:
	Authorization Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	BYTE HTTPNeedsAuth(BYTE* cFile)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPNeedsAuth(BYTE* cFile)
{
	// If the filename begins with the folder "protect", then require auth
	if(memcmppgm2ram(cFile, (ROM void*)"protect", 7) == 0)
		return 0x00;		// Authentication will be needed later

	// If the filename begins with the folder "snmp", then require auth
	if(memcmppgm2ram(cFile, (ROM void*)"snmp", 4) == 0)
		return 0x00;		// Authentication will be needed later

	#if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
	if(memcmppgm2ram(cFile, (ROM void*)"mpfsupload", 10) == 0)
		return 0x00;
	#endif

	// You can match additional strings here to password protect other files.
	// You could switch this and exclude files from authentication.
	// You could also always return 0x00 to require auth for all files.
	// You can return different values (0x00 to 0x79) to track "realms" for below.

	return 0x80;			// No authentication required
}
#endif

/*****************************************************************************
  Function:
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
	if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0
		&& strcmppgm2ram((char *)cPass, (ROM char *)"microchip") == 0)
		return 0x80;		// We accept this combination
	
	// You can add additional user/pass combos here.
	// If you return specific "realm" values above, you can base this 
	//   decision on what specific file or folder is being accessed.
	// You could return different values (0x80 to 0xff) to indicate 
	//   various users or groups, and base future processing decisions
	//   in HTTPExecuteGet/Post or HTTPPrint callbacks on this value.
	
	return 0x00;			// Provided user/pass is invalid
}
#endif

/****************************************************************************
  Section:
	GET Form Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecuteGet(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
	BYTE *ptr;
	BYTE filename[20];
	
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, 20);
	
	// If its the forms.htm page
	if(!memcmppgm2ram(filename, "forms.htm", 9))
	{
		// Seek out each of the four LED strings, and if it exists set the LED states
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"led4");
		if(ptr)
			LED4_IO = (*ptr == '1');

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"led3");
		if(ptr)
			LED3_IO = (*ptr == '1');

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"led2");
		if(ptr)
			LED2_IO = (*ptr == '1');

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"led1");
		if(ptr)
			LED1_IO = (*ptr == '1');
	}
	
	// If it's the LED updater file
	else if(!memcmppgm2ram(filename, "cookies.htm", 11))
	{
		// This is very simple.  The names and values we want are already in
		// the data array.  We just set the hasArgs value to indicate how many
		// name/value pairs we want stored as cookies.
		// To add the second cookie, just increment this value.
		// remember to also add a dynamic variable callback to control the printout.
		curHTTP.hasArgs = 0x01;
	}
		
	
	// If it's the LED updater file
	else if(!memcmppgm2ram(filename, "leds.cgi", 8))
	{
		// Determine which LED to toggle
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"led");
		
		// Toggle the specified LED
		switch(*ptr) {
			case '1':
				LED1_IO ^= 1;
				break;
			case '2':
				LED2_IO ^= 1;
				break;
			case '3':
				LED3_IO ^= 1;
				break;
			case '4':
				LED4_IO ^= 1;
				break;
			case '5':
				LED5_IO ^= 1;
				break;
			case '6':
				LED6_IO ^= 1;
				break;
			case '7':
				LED7_IO ^= 1;
				break;
		}
		
	}
	
	return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
	POST Form Handlers
  ***************************************************************************/
#if defined(HTTP_USE_POST)

/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecutePost(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
	// Resolve which function to use and pass along
	BYTE filename[20];
	
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

	if(!strcmppgm2ram((char*)filename, "index.htm"))
		return HTTPPostGame();

	return HTTP_IO_DONE;
}

static HTTP_IO_RESULT HTTPPostGame(void)
{
    BYTE cmd[8];
    BYTE arg[HTTP_MAX_DATA_LEN];

    if(TCPIsGetReady(sktHTTP) < curHTTP.byteCount)
	return HTTP_IO_NEED_DATA;

    // Read all browser POST data
    while(curHTTP.byteCount)
    {
        // Parse the value that was read
	if(HTTPReadPostName(cmd, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
		return HTTP_IO_NEED_DATA;

        if(!strcmppgm2ram((char*)cmd, (ROM char*)"level"))
            if(HTTPReadPostValue(arg, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;
    }

    char test[200];
    sprintf(test, "Level to load : %d\n", atoi(arg));
    MyConsole_SendMsg(test);

    // encode to memory buffer
    char buffer[256];
    mpack_writer_t writer;
    mpack_writer_init_buffer(&writer, buffer, sizeof(buffer));

    // write the example on the msgpack homepage
    mpack_start_map(&writer, 2);

    mpack_write_cstr(&writer, "msgtype");
    mpack_write_u8(&writer, 1);

    mpack_write_cstr(&writer, "value");
    mpack_write_u8(&writer, (unsigned int) atoi(arg));

    mpack_finish_map(&writer);

    size_t count = mpack_writer_buffer_used(&writer);
    MyCyclone_Send(buffer, count, 1);

    return HTTP_IO_DONE;
}

#endif //(use_post)


/****************************************************************************
  Section:
	Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
	void HTTPPrint_varname(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/

void HTTPPrint_state(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.state);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_lives(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.lives);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_ball(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.nbballs);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_bricks(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.rbricks);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_score(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.score);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_size(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.padsize);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

void HTTPPrint_speed(void)
{
    char value[30];
    sprintf(value, "%d", MyGame.speed);
    TCPPutROMString(sktHTTP, (ROM BYTE*)value);
}

#endif
