/*******************************************************************************
* Header file for MyRPC                                                        *
*******************************************************************************/

#ifndef MYRPC_H
#define	MYRPC_H

#define CYCLONE_RPC_MIWI 0
#define CYCLONE_RPC_FILE 1
#define CYCLONE_RPC_INFO 2

/*******************************************************************************
* Functions Prototypes                                                         *
*******************************************************************************/

void            MyRPC_MIWI(char * msg, size_t len);
void            MyRPC_File(char * msg, size_t len);
void            MyRPC_Info(char * msg, size_t len);

/*******************************************************************************
* Global Variables for MyRPC Functions                                         *
*******************************************************************************/

#ifdef   MyRPC

#endif

#endif	/* MYRPC_H */

