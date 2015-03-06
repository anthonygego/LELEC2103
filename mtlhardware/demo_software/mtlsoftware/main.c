// --------------------------------------------------------------------
// Copyright (c) 2010 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------

#include "terasic_includes.h"
#include "multi_touch.h"
#include "gui.h"


int main()
{
   //const alt_u32 TouchI2cAddr = 0x10;

    
    // touch
    MTC_INFO *pTouch;
    printf("Terasic Painter Demo\r\n");
    
    pTouch = MTC_Init(MULTI_TOUCH_BASE, MULTI_TOUCH_IRQ);
    if (!pTouch){
        printf("Failed to init multi-touch\r\n");
    }else{
        printf("Init touch successfully\r\n");
    }    
    
    GUI(pTouch);          

  return 0;
}





