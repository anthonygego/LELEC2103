/*******************************************************************************
* MyConsole                                                                    *
********************************************************************************
* Description:                                                                 *
* Functions to send and receive data from the Console                          *
********************************************************************************
* Version : 1.00 - June 2011                                                   *
*******************************************************************************/

/*  
*   The Console uses UART2A
*       U2ARTS = RG6
*       U2ARX = RG7
*       U2ATX = RG8
*       U2ACTS = RG9
*
*   Install Driver for FDTI chip : http://www.ftdichip.com/Drivers/VCP.htm
*
*   Terminal Emulation on MAC/Linux/PC
*       on MAC : QuickTerm - http://www.macupdate.com/app/mac/19751/quickterm
*       on MAC/Linux : Use 'screen' as a serial terminal emulator : http://hints.macworld.com/article.php?story=20061109133825654
*       on PC : HyperTerminal
*/


#define  MyCONSOLE

#include "MyApp.h"
#include "mpack.h"

void MyConsole_Init(void)
{
    UARTConfigure(UART2A, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART2A, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART2A, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART2A, GetPeripheralClock(), 9600);
    UARTEnable(UART2A, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    ptrCmd = theCmd;
}

void MyConsole_SendMsg(const char *theMsg)
{
    while(*theMsg != '\0')
    {
        while(!UARTTransmitterIsReady(UART2A));
        UARTSendDataByte(UART2A, *theMsg);
        theMsg++;
    }
    while(!UARTTransmissionHasCompleted(UART2A));
}

BOOL MyConsole_GetCmd(void)
{
    if (!UARTReceivedDataIsAvailable(UART2A))
        return FALSE;
    *ptrCmd = UARTGetDataByte(UART2A);
    
    // Do echo
    while(!UARTTransmitterIsReady(UART2A));
    UARTSendDataByte(UART2A, *ptrCmd);
    
    switch (*ptrCmd) {
        case '\r':
            *ptrCmd = '\0';
            ptrCmd = theCmd;
            return TRUE;
        case '\n':
            break;
        default:  
//            if ((theCmd+sizeCmd-1) > ptrCmd)
                ptrCmd++;
            break;
    }
    return FALSE;
}

void MyConsole_Task(void)
{
    unsigned char theStr[64];

    if (!MyConsole_GetCmd()) return;

    if (strcmp(theCmd, "MyTest") == 0) {

        MyConsole_SendMsg("MyTest ok\n>");

    } else if (strcmp(theCmd, "MyCyclone") == 0) {

        // encode to memory buffer
        char buffer[256];
        mpack_writer_t writer;
        mpack_writer_init_buffer(&writer, buffer, sizeof(buffer));

        // write the example on the msgpack homepage
        mpack_start_map(&writer, 2);
        mpack_write_cstr(&writer, "compact");
        mpack_write_bool(&writer, TRUE);
        mpack_write_cstr(&writer, "schema");
        mpack_write_uint(&writer, 42);
        mpack_finish_map(&writer);

        // clean up
        size_t count = mpack_writer_buffer_used(&writer);

        MyCyclone_Send(buffer, count, 1);

    } else if (strcmp(theCmd, "MyMPack") == 0 ) {

        // encode to memory buffer
        char buffer[256];
        mpack_writer_t writer;
        mpack_writer_init_buffer(&writer, buffer, sizeof(buffer));

        // write the example on the msgpack homepage
        mpack_start_map(&writer, 2);
        mpack_write_cstr(&writer, "compact");
        mpack_write_bool(&writer, TRUE);
        mpack_write_cstr(&writer, "schema");
        mpack_write_uint(&writer, 42);
        mpack_finish_map(&writer);

        // clean up
        size_t count = mpack_writer_buffer_used(&writer);

        // parse a data buffer into a node tree
        mpack_tree_t tree;
        mpack_tree_init(&tree, buffer, count);
        mpack_node_t* root = mpack_tree_root(&tree);

        // extract the example data on the msgpack homepage
        BOOL compact = mpack_node_bool(mpack_node_map_cstr(root, "compact"));
        int schema = mpack_node_i32(mpack_node_map_cstr(root, "schema"));

        // clean up and check for errors
        if (mpack_tree_destroy(&tree) != mpack_ok)
            return;

        sprintf(theStr, "Read value : %d - %d\n>", compact, schema);
        MyConsole_SendMsg(theStr);

    } else if (strcmp(theCmd, "MyCAN") == 0) {

        MyCAN_TxMsg(0x200, "0123456");
        MyConsole_SendMsg("Send CAN Msg 0x200 '0123456'\n>");

    } else if (strcmp(theCmd, "MyMIWI-B") == 0) {

        MyMIWI_Send(myMIWI_EnableBroadcast, "0123456", 8);
        MyConsole_SendMsg("Send MIWI Broadcast Msg '0123456'\n>");

    } else if (strcmp(theCmd, "MyMIWI-U") == 0) {

        MyMIWI_Send(myMIWI_DisableBroadcast, "0123456", 8);
        MyConsole_SendMsg("Send MIWI Unicast Msg '0123456'\n>");

    } else if (strcmp(theCmd, "MyPing") == 0) {

        MyPing_Flag = TRUE;

    } else if (strcmp(theCmd, "MyMail") == 0) {

        MyMail_Flag = TRUE;

    } else if (strcmp(theCmd, "MyRTCC") == 0) {

        MyRTCC_SetTime();
        MyRTCC_GetTime();

    } else if (strcmp(theCmd, "MyTime") == 0) {

        MyRTCC_GetTime();

    } else if (strcmp(theCmd, "MyIO") == 0) {

        // Display Msg on the Console
        MyConsole_SendMsg("MyExpansionBoard_IO : Output = 5 - AA - 55 - AA\n>");

    } else if (strcmp(theCmd, "MyFlash") == 0) {

        MyFlash_Erase();
        MyFlash_Test();

    } else if (strcmp(theCmd, "MyTemp") == 0) {

        int  theTemperature;

        theTemperature = MyTemperature_Read();
        if (theTemperature >= 0x80)
            theTemperature |= 0xffffff00;   // Sign Extend
        sprintf(theStr, "Temperature : %d°\n", theTemperature);
        MyConsole_SendMsg(theStr);

    } else if (strcmp(theCmd, "MyMDDFS") == 0) {

        mPORTBSetPinsDigitalIn(USD_CD);
        MyMDDFS_Test();

    } else {
        MyConsole_SendMsg("Unknown Command\n>");
    }
}

/*******************************************************************************
 * Functions needed for Wireless Protocols (MiWI)
 * ****************************************************************************/

ROM unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void ConsolePutROMString(ROM char* str)
{
    BYTE c;
    while( (c = *str++) )
        ConsolePut(c);
}

void ConsolePut(BYTE c)
{
    while(!UARTTransmitterIsReady(UART2A));
    UARTSendDataByte(UART2A, c);
}

BYTE ConsoleGet(void)
{
    char Temp;
    while(!UARTReceivedDataIsAvailable(UART2A));
    Temp = UARTGetDataByte(UART2A);
    return Temp;
}

void PrintChar(BYTE toPrint)
{
    BYTE PRINT_VAR;
    PRINT_VAR = toPrint;
    toPrint = (toPrint>>4)&0x0F;
    ConsolePut(CharacterArray[toPrint]);
    toPrint = (PRINT_VAR)&0x0F;
    ConsolePut(CharacterArray[toPrint]);
    return;
}

void PrintDec(BYTE toPrint)
{
    ConsolePut(CharacterArray[toPrint/10]);
    ConsolePut(CharacterArray[toPrint%10]);
}
