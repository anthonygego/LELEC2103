/*************************************************************************
* MyCyclone                                                              *
**************************************************************************
* Description:                                                           *
* Functions to control the Cyclone IV/Nios II                            *
**************************************************************************
* Version : 1.00 - Sept 2011                                             *
**************************************************************************/

#define  MyCYCLONE

#include "MyApp.h"
#include "MDDFileSystem/FSIO.h"

pic32_txrx_state pic32_state;

void MyCyclone_Write(unsigned int theAddress, unsigned int theData)
{
    unsigned int intStatus;

    intStatus = INTDisableInterrupts();
    mPORTEClearBits(CS_FPGA);
    MySPI_PutC(theAddress | 0x80); // Bit 7 = R/W = 1
    MySPI_PutC(theData);
    mPORTESetBits(CS_FPGA);
    INTRestoreInterrupts(intStatus);
}

unsigned int MyCyclone_Read(unsigned int theAddress)
{
    unsigned int theData;
    unsigned int intStatus;

    intStatus = INTDisableInterrupts();
    mPORTEClearBits(CS_FPGA);
    MySPI_PutC(theAddress & 0x7F);   // Bit 7 = R/W = 0
    theData = MySPI_GetC();
    mPORTESetBits(CS_FPGA);
    INTRestoreInterrupts(intStatus);
    return(theData);
}

void MyCyclone_SendAck()
{
    while(!pic32_state.can_send);
    MyCyclone_Write(CYCLONE_TXSTATUS, CYCLONE_ACK_MASK);
    mPORTDSetBits(INT2);
    mPORTDClearBits(INT2);
}

void MyCyclone_Init(void)
{
    // Configure Reset Pin = GPIO_2[10] = RD7
    mPORTDSetBits(RST_FPGA);
    mPORTDSetPinsDigitalOut(RST_FPGA);

    // Do Interrupt Initialization
    // Set INT1 as input, INT2 as output
    mPORTDSetPinsDigitalIn(INT1);
    mPORTDSetPinsDigitalOut(INT2);
    mPORTDClearBits(INT2);

    // Do a Reset
    mPORTDClearBits(RST_FPGA);
    mPORTDSetBits(RST_FPGA);

    // Clear corresponding bits in INTCON for falling edge trigger
    INTCONCLR = _INTCON_INT1EP_MASK;

    // Set up interrupt prioirty and sub-priority
    INTSetVectorPriority(INT_EXTERNAL_1_VECTOR, My_INT_EXTERNAL_1_PRIORITY);
    INTSetVectorSubPriority(INT_EXTERNAL_1_VECTOR, My_INT_EXTERNAL_1_SUB_PRIORITY);

    // Clear the interrupt flag
    INTClearFlag(INT_INT1);

    // Enable INT1
    INTEnable(INT_INT1, INT_ENABLED);

    // Init SPI state
    pic32_state.size = 0;
    pic32_state.cnt = 0;
    pic32_state.can_send = TRUE;
    pic32_state.transfer_done = FALSE;
    pic32_state.type = FALSE;
    pic32_state.buffer = NULL;
}

void __ISR(_EXTERNAL_1_VECTOR, My_INT_EXTERNAL_1_IPL) _External1InterruptHandler(void)
{
    unsigned int intStatus;
    intStatus = INTDisableInterrupts();
    // Clear the interrupt flags
    INTClearFlag(INT_INT1);

    int status = MyCyclone_Read(CYCLONE_RXSTATUS);
    
    if(status & CYCLONE_INIT_MASK)
    {
        pic32_state.size = 0;
        pic32_state.cnt = 0;
        pic32_state.can_send = TRUE;
        pic32_state.transfer_done = FALSE;
        pic32_state.type = status & CYCLONE_TYPE_MASK;
        pic32_state.buffer = NULL;
        MyCyclone_SendAck();
    }
    else if(status & CYCLONE_ACK_MASK)
        pic32_state.can_send = TRUE;
    else
    {
        if(status & CYCLONE_SIZE_MASK)
                pic32_state.size = (pic32_state.size << 8) + MyCyclone_Read(CYCLONE_RXDATA);
        else
        {
            if(status & CYCLONE_START_MASK)
            {
                    pic32_state.buffer = malloc(sizeof(char)*pic32_state.size);
                    pic32_state.cnt = 0;
            }

            pic32_state.buffer[pic32_state.cnt++] = MyCyclone_Read(CYCLONE_RXDATA);

            if(status & CYCLONE_END_MASK)
                pic32_state.transfer_done = 1;
        }
        MyCyclone_SendAck();
    }
    
    INTRestoreInterrupts(intStatus);
}

BOOL MyCyclone_Receive(BYTE ** buffer, size_t * length, BOOL * type)
{
    if(!pic32_state.transfer_done)
        return FALSE;
    else
    {
        pic32_state.transfer_done = 0;
        *buffer = pic32_state.buffer;
        *length = pic32_state.size;
        *type = pic32_state.type;
        return TRUE;
    }
}

void MyCyclone_SendByte(BYTE data, size_t index, size_t total_length, BOOL type)
{
    if(index == 0)
    {
        while(!pic32_state.can_send);
        MyCyclone_Write(CYCLONE_TXSTATUS, CYCLONE_INIT_MASK | (type ? CYCLONE_TYPE_MASK : 0));
        pic32_state.can_send = FALSE;
        mPORTDSetBits(INT2);
        mPORTDClearBits(INT2);
        while(!pic32_state.can_send);

        int i;
        for(i=sizeof(size_t)-1; i >=0; i--)
        {
            while(!pic32_state.can_send);
            MyCyclone_Write(CYCLONE_TXDATA, (total_length >> 8*i) & 0xff);
            MyCyclone_Write(CYCLONE_TXSTATUS, CYCLONE_SIZE_MASK | (type ? CYCLONE_TYPE_MASK : 0));
            pic32_state.can_send = FALSE;
            mPORTDSetBits(INT2);
            mPORTDClearBits(INT2);
            while(!pic32_state.can_send);
        }
    }

    while(!pic32_state.can_send);
    MyCyclone_Write(CYCLONE_TXDATA, data);
    if((index <= 1) || (index >= total_length-2))
        MyCyclone_Write(CYCLONE_TXSTATUS, (index == 0 ? CYCLONE_START_MASK : 0) | (index==total_length-1 ? CYCLONE_END_MASK : 0) | (type ? CYCLONE_TYPE_MASK : 0) );
    pic32_state.can_send = FALSE;
    mPORTDSetBits(INT2);
    mPORTDClearBits(INT2);
    while(!pic32_state.can_send);
}

void MyCyclone_Send(BYTE * data, size_t length, BOOL type)
{
    int i;
    for(i=0; i < length; i++)
        MyCyclone_SendByte(data[i], i, length, type);
}

int MyCyclone_SendFile(char *filename)
{
   FSFILE		*file;
   BYTE         	pChar[8192];
   long			position;
   long                 filesize;
   unsigned char        tabWrite[100];

   sprintf(tabWrite, ">>Sending file %s.\n", filename);
   MyConsole_SendMsg(tabWrite);

   MyMDDFS_SaveSPI();

   if (!MDD_MediaDetect()) {
       MyMDDFS_RestoreSPI();
       MyConsole_SendMsg("MyMDDFS - Error MDD_MediaDetect\n>");
       return 1;
   }

   if (!FSInit()) {
       MyMDDFS_RestoreSPI();
       MyConsole_SendMsg("MyMDDFS - Error FSInit\n>");
       return 1;
   }

   file = FSfopen(filename, "r");
   if (file == NULL) {
       MyConsole_SendMsg(">MyMDDFS - File not found\n");
       return 1;
   }

   filesize =  file->size;
   FSfclose(file);

   MyMDDFS_RestoreSPI();

   position = 0L;
   while(position < filesize)
   {
       MyMDDFS_SaveSPI();

       if (!MDD_MediaDetect()) {
           MyMDDFS_RestoreSPI();
           MyConsole_SendMsg("MyMDDFS - Error MDD_MediaDetect\n>");
           return 1;
       }

       if (!FSInit()) {
           MyMDDFS_RestoreSPI();
           MyConsole_SendMsg("MyMDDFS - Error FSInit\n>");
           return 1;
       }

       file = FSfopen(filename, "r");
       if (file == NULL) {
           MyConsole_SendMsg(">MyMDDFS - File not found\n");
           return 1;
       }

       FSfseek(file, position, SEEK_SET);
       int readsize = FSfread(pChar, sizeof(char), 8192, file);

       FSfclose(file);
       MyMDDFS_RestoreSPI();

       int k;
       for(k=0; k < readsize; k++)
           MyCyclone_SendByte(pChar[k], position+k, filesize, 0);

       position = position + readsize;

       sprintf(tabWrite, ">Sent %d bytes\n", position);
       MyConsole_SendMsg(tabWrite);
   }
   MyConsole_SendMsg("\n>");
}

void MyCyclone_Task(void)
{
    BYTE * msg;
    BOOL type;
    size_t len;
    char theStr[100];

    if(MyCyclone_Receive(&msg, &len, &type))
    {
        sprintf(theStr, "Message%s of size %d : %s\n", type ? " (RPC)" : "", len, msg);
        MyConsole_SendMsg(theStr);
        MyConsole_SendMsg("MyTest ok \n>");
    }
}