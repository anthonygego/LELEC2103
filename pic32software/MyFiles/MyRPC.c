/*******************************************************************************
* MyRPC                                                                       *
********************************************************************************
* Description:                                                                 *
* Treats RPC messages received via networks                                    *
********************************************************************************
* Version : 1.00 - March 2015                                                  *
*******************************************************************************/

#include "MyApp.h"

void MyRPC_MIWI(char * msg, size_t len)
{
    MyMIWI_Send(myMIWI_DisableBroadcast, msg, len);
}

void MyRPC_File(char * msg, size_t len)
{
    MyCyclone_SendFile(msg);
}
