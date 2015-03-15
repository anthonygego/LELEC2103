/*******************************************************************************
* MyMIWI                                                                       *
********************************************************************************
* Description:                                                                 *
* Functions to control the Module 802.15.4 - MRF24J40MB                        *
********************************************************************************
* Version : 1.00 - July 2011                                                   *
*******************************************************************************/

/* Modifications to the Microchip MIWI Library : MRF24J40.c
 *
 *  Line 1593 - Routine HighISR
 *      Commment : void __ISR(_EXTERNAL_1_VECTOR, ipl4) _INT1Interrupt(void)
 *      Add      : void __ISR(_EXTERNAL_3_VECTOR, ipl4) _INT3Interrupt(void)
 *
 *  Disable all interrupts during SPI access
 *      PHYSetLongRAMAddr, PHYSetShortRAMAddr, PHYGetShortRAMAddr, PHYGetLongRAMAddr
 */
#define  MyMIWI_NODE1       // #define EUI_0 0x01 in ConfigApp.h
//#define  MyMIWI_NODE2       // #define EUI_0 0x03 in ConfigApp.h

#if defined(MyMIWI_NODE1) && defined(MyMIWI_NODE2)
    #error "Only 1 node must be defined"
#endif
#if !defined(MyMIWI_NODE1) && !defined(MyMIWI_NODE2)
    #error "1 node must be defined"
#endif

#define  MyMIWI

#include "MyApp.h"

/******************************************************************************/

// Implementation of MSPI.c

void SPIPut(BYTE v) { MySPI_PutC((unsigned int) v); }
BYTE SPIGet(void)   { return ((BYTE) MySPI_GetC()); }

/******************************************************************************/

miwi_txrx_state miwi_state;

/******************************************************************************/

void MyMIWI_Init(void) {

    // Configure Pins for MRF24J40MB
    mPORTESetBits(RST_MIWI);
    mPORTESetPinsDigitalOut(RST_MIWI);

    mPORTBSetBits(MIWI_WAKE);
    mPORTBSetPinsDigitalOut(MIWI_WAKE);

    // Configure the INT3 controller for MIWI
    // Set RD10/INT3 as input
    mPORTDSetPinsDigitalIn(BIT_10);
    // Clear corresponding bits in INTCON for falling edge trigger
    INTCONCLR = _INTCON_INT3EP_MASK;
    // Set up interrupt prioirty and sub-priority
    INTSetVectorPriority(INT_EXTERNAL_3_VECTOR, My_INT_EXTERNAL_3_PRIORITY);
    INTSetVectorSubPriority(INT_EXTERNAL_3_VECTOR, My_INT_EXTERNAL_3_SUB_PRIORITY);
    // Clear the interrupt flags
    INTClearFlag(INT_INT3);
    // Enable INT3
    INTEnable(INT_INT3, INT_ENABLED);

    // WARNING : Change in file MRF24J40.c in Microchip Application Library
    // the line : void __ISR(_EXTERNAL_1_VECTOR, ipl4) _INT1Interrupt(void)
    // by       : void __ISR(_EXTERNAL_3_VECTOR, ipl4) _INT3Interrupt(void)
}

void MyMIWI_Start(void) {
    
    BYTE    i;
    char    theStr[64];

    /*******************************************************************/
    // Initialize Microchip proprietary protocol. Which protocol to use
    // depends on the configuration in ConfigApp.h
    /*******************************************************************/
    /*******************************************************************/
    // Function MiApp_ProtocolInit initialize the protocol stack. The
    // only input parameter indicates if previous network configuration
    // should be restored. In this simple example, we assume that the
    // network starts from scratch.
    /*******************************************************************/
    MiApp_ProtocolInit(FALSE);

    // Set default channel
    if( MiApp_SetChannel(myMIWI_Channel) == FALSE )
    {
        Printf("\r\nSelection of channel ");
        PrintDec(myMIWI_Channel);
        Printf(" is not supported in current condition.\r\n");
        return;
    }

    /*******************************************************************/
    // Function MiApp_ConnectionMode defines the connection mode. The
    // possible connection modes are:
    //  ENABLE_ALL_CONN:    Enable all kinds of connection
    //  ENABLE_PREV_CONN:   Only allow connection already exists in
    //                      connection table
    //  ENABL_ACTIVE_SCAN_RSP:  Allow response to Active scan
    //  DISABLE_ALL_CONN:   Disable all connections.
    /*******************************************************************/
    MiApp_ConnectionMode(ENABLE_ALL_CONN);

    /*******************************************************************/
    // Function MiApp_EstablishConnection try to establish a new
    // connection with peer device.
    // The first parameter is the index to the active scan result, which
    //      is acquired by discovery process (active scan). If the value
    //      of the index is 0xFF, try to establish a connection with any
    //      peer.
    // The second parameter is the mode to establish connection, either
    //      direct or indirect. Direct mode means connection within the
    //      radio range; Indirect mode means connection may or may not
    //      in the radio range.
    /*******************************************************************/

#if defined(MyMIWI_NODE1)
    i = MiApp_EstablishConnection(0xFF, CONN_MODE_DIRECT);
#else
    while( (i = MiApp_EstablishConnection(0xFF, CONN_MODE_DIRECT)) == 0xFF );
#endif

    if(i != 0xFF) {
        sprintf(theStr, "Connected Peer  on Channel %d\n>", myMIWI_Channel);
        MyConsole_SendMsg(theStr);
    }
    else {
        
    /*******************************************************************/
    // If no network can be found and join, we need to start a new 
    // network by calling function MiApp_StartConnection
    //
    // The first parameter is the mode of start connection. There are 
    // two valid connection modes:
    //   - START_CONN_DIRECT        start the connection on current 
    //                              channel
    //   - START_CONN_ENERGY_SCN    perform an energy scan first, 
    //                              before starting the connection on 
    //                              the channel with least noise
    //   - START_CONN_CS_SCN        perform a carrier sense scan 
    //                              first, before starting the 
    //                              connection on the channel with 
    //                              least carrier sense noise. Not
    //                              supported for current radios
    //
    // The second parameter is the scan duration, which has the same 
    //     definition in Energy Scan. 10 is roughly 1 second. 9 is a 
    //     half second and 11 is 2 seconds. Maximum scan duration is 
    //     14, or roughly 16 seconds.
    //
    // The third parameter is the channel map. Bit 0 of the 
    //     double word parameter represents channel 0. For the 2.4GHz 
    //     frequency band, all possible channels are channel 11 to 
    //     channel 26. As the result, the bit map is 0x07FFF800. Stack 
    //     will filter out all invalid channels, so the application 
    //     only needs to pay attention to the channels that are not 
    //     preferred.
    /*******************************************************************/
        MiApp_StartConnection(START_CONN_DIRECT, 10, 0);
        MyConsole_SendMsg("Start Connection\n>");
    }

    /*******************************************************************/
    // Function DumpConnection is used to print out the content of the
    //  Connection Entry on the hyperterminal. It may be useful in
    // the debugging phase.
    // The only parameter of this function is the index of the
    // Connection Entry. The value of 0xFF means to print out all
    //  valid Connection Entry; otherwise, the Connection Entry
    // of the input index will be printed out.
    /*******************************************************************/
    DumpConnection(0xFF);
}

/******************************************************************************/
union bin_int
{
    int integer;
    BYTE byte[4];
};

BOOL MyMIWI_RxData(BOOL* ack, int* position, BYTE *data, size_t* size)
{
    int i;

    /*******************************************************************/
    // Function MiApp_MessageAvailable returns a boolean to indicate if
    //  a packet has been received by the transceiver. If a packet has
    //  been received, all information will be stored in the rxFrame,
    //  structure of RECEIVED_MESSAGE.
    /*******************************************************************/
    if( !MiApp_MessageAvailable() )
        return FALSE;

    /*******************************************************************/
    // If a packet has been received, following code prints out some of
    // the information available in rxMessage.
    /*******************************************************************/

    *size = rxMessage.PayloadSize - 5;
    *ack = (BOOL) rxMessage.Payload[0];
    union bin_int u;
    for(i=0; i<4; i++)
        u.byte[i] = rxMessage.Payload[i+1];

    *position = u.integer;

    for(i = 5; i < rxMessage.PayloadSize; i++)
        *data++ = rxMessage.Payload[i];

    /*******************************************************************/
    // Function MiApp_DiscardMessage is used to release the current
    //  received packet.
    // After calling this function, the stack can start to process the
    //  next received frame
    /*******************************************************************/
    MiApp_DiscardMessage();

    return TRUE;
}

void MyMIWI_TxData(BOOL enableBroadcast,BOOL ack, int position, BYTE *data, size_t size)
{
    if(position > 2048)
       return;

    MiApp_FlushTx();
    int i;
    MiApp_WriteData((BYTE) ack);

    union bin_int u;
    u.integer = position;
    for(i=0; i < 4; i++)
        MiApp_WriteData(u.byte[i]);

    for(i=0; i < size; i++)
        MiApp_WriteData((BYTE) data[i]);

    if (enableBroadcast) {

        /*******************************************************************/
        // Function MiApp_BroadcastPacket is used to broadcast a message
        //    The only parameter is the boolean to indicate if we need to
        //       secure the frame
        /*******************************************************************/
        MiApp_BroadcastPacket(FALSE);

    } else {

        /*******************************************************************/
        // Function MiApp_UnicastConnection is one of the functions to
        //  unicast a message.
        //    The first parameter is the index of Connection Entry for
        //       the peer device. In this demo, since there are only two
        //       devices involved, the peer device must be stored in the
        //       first Connection Entry
        //    The second parameter is the boolean to indicate if we need to
        //       secure the frame. If encryption is applied, the security
        //       key are defined in ConfigApp.h
        //
        // Another way to unicast a message is by calling function
        //  MiApp_UnicastAddress. Instead of supplying the index of the
        //  Connection Entry of the peer device, this function requires the
        //  input parameter of destination address.
        /*******************************************************************/
        if( MiApp_UnicastConnection(0, FALSE) == FALSE )
            Printf("\r\nUnicast Failed\r\n");
    }

}

BOOL  MyMIWI_Reveice(BYTE * data, size_t * length)
{
    if(!miwi_state.transfer_done)
        return FALSE;
    else
    {
        miwi_state.transfer_done = FALSE;
        *length = miwi_state.size;
        memcpy(data, miwi_state.buffer,miwi_state.size);
    }
}

int MyMIWI_Send(BOOL enableBroadcast, BYTE * buf, size_t length)
{
   size_t  position;
   BYTE    theData[64];
   BOOL    readack;
   int     readpos;
   size_t  read_size;
   int     timer = 0;
   BOOL    result;

   if(length > 2048)
       return -1;

   position = 0;
   while(position < length)
   {
       size_t readsize = min(length-position, 30);
       MyMIWI_TxData(enableBroadcast, FALSE, position, buf, readsize);

       result = MyMIWI_RxData(&readack,&readpos, theData, &read_size);
       int retries = 0;
       while ((!result || !readack || (readpos != position)) && retries < 5)
       {
           if(timer == 100000)
           {
               MyMIWI_TxData(enableBroadcast, FALSE, position, buf, readsize);
               retries++;
               timer = 0;
           }
           else
               timer++;

           result = MyMIWI_RxData(&readack,&readpos, theData, &read_size);
       }
       if(retries == 5) break;

       buf = buf + readsize;
       position = position + readsize;
   }

   MyMIWI_TxData(enableBroadcast, FALSE, position, "", 0);

   result = MyMIWI_RxData(&readack,&readpos, theData, &read_size);
   int retries = 0;
   while ((!result || !readack || (readpos != position)) && retries < 5)
   {
       if(timer == 100000)
       {
           MyMIWI_TxData(enableBroadcast, FALSE, position, "", 0);
           retries++;
           timer = 0;
       }
       else
           timer++;

       result = MyMIWI_RxData(&readack,&readpos, theData, &read_size);
   }
}

/******************************************************************************/

void MyMIWI_Task(void) {
    /* Management of data packets */
    BOOL ack;
    int position;
    BYTE data[64];
    size_t size;
    BOOL result = MyMIWI_RxData(&ack, &position, data, &size);
    if (result && !ack) {
        MyMIWI_TxData(myMIWI_EnableBroadcast, TRUE, position, (BYTE*) "Ack MIWI", 9);
        if(size == 0)
        {
            miwi_state.transfer_done = TRUE;
            miwi_state.size = position;
        }
        else
        {
            miwi_state.transfer_done = FALSE;
            int i;
            for(i=0; i < size; i++)
                miwi_state.buffer[position+i] = data[i];
        }
    }

    /* Management of messages */
    char theStr[128];
    BYTE msg[2048];
    if(MyMIWI_Reveice(msg, &size))
    {
       sprintf(theStr, "Received data of size : %d \n>", miwi_state.size);
       MyConsole_SendMsg(theStr);
       MyConsole_SendMsg(msg);
       MyConsole_SendMsg("\n>");
    }
}

/******************************************************************************/