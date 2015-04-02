/*******************************************************************************
* MyRPC                                                                       *
********************************************************************************
* Description:                                                                 *
* Treats RPC messages received via networks                                    *
********************************************************************************
* Version : 1.00 - March 2015                                                  *
*******************************************************************************/

#include "MyApp.h"
#include "mpack.h"

void MyRPC_MIWI(char * msg, size_t len)
{
    MyMIWI_Send(myMIWI_DisableBroadcast, msg, len);
}

void MyRPC_File(char * msg, size_t len)
{
    MyCyclone_SendFile(msg);
}

void MyRPC_Info(char * msg, size_t len)
{
    // parse a data buffer into a node tree
    mpack_tree_t tree;
    mpack_tree_init(&tree, msg, len);
    mpack_node_t* root = mpack_tree_root(&tree);

    MyGame.state = mpack_node_i32(mpack_node_map_cstr(root, "state"));
    MyGame.lives = mpack_node_i32(mpack_node_map_cstr(root, "lives"));
    MyGame.rbricks = mpack_node_i32(mpack_node_map_cstr(root, "bricks"));
    MyGame.padsize = mpack_node_i32(mpack_node_map_cstr(root, "padsize"));
    MyGame.speed = mpack_node_i32(mpack_node_map_cstr(root, "speed"));
    MyGame.score = mpack_node_i32(mpack_node_map_cstr(root, "score"));

    // clean up and check for errors
    mpack_tree_destroy(&tree);

    free(msg);
}