/*
 * ILI9341.c
 *
 *  Created on: 2014-2-13
 *      Author: Administrator
 */

//#include "terasic_includes.h"
#include <io.h>
#include <stdlib.h>
#include "ILI9341.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
//#include "type.h"
#include "stdio.h"
#include <unistd.h>
#include <alt_types.h>
/*
The chip-select CSX (active
low) is used to enable or disable ILI9341 chip.
The RESX (active low) is an external reset signal.
WRX is the parallel data write strobe, RDX is the parallel data read strobe and D[17:0] is parallel data bus.
ILI9341  latches  the  input  data  at  the  rising  edge  of  WRX  signal.
The  D/CX  is  the  signal  of  data/command selection.
When  D/CX=¡¯1¡¯,  D  [17:0]  bits  are  display  RAM  data  or  command¡¯s  parameters.
When  D/CX=¡¯0¡¯,  D [17:0] bits are commands.
*/

#define  Set_LCD_RST  IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_N_BASE,0x01)
#define  Clr_LCD_RST  IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_N_BASE,0x00)



void lcd_pattern_horizon(lcd_info *p);
void lcd_pattern_vertical(lcd_info *p);
//void lcd_DrawPoint(alt_u16 x,alt_u16 y,alt_u16 color );
#define RED 0xf800
#define GREEN 0x07e0
#define BLUE 0x001f
#define BLACK  0x0000
#define WHITE 0xffff

void delay_ms(alt_u16 count_ms)
{
    while(count_ms--)
    {
        usleep(1000);
    }
}


void lcd_set_cursor(lcd_info *p, alt_u16 Xpos, alt_u16 Ypos)
{
	 IOWR(p->BASE, 0x00, 0x002A);
		 IOWR(p->BASE, 0x01, Xpos>>8);
		 IOWR(p->BASE, 0x01, Xpos&0XFF);
	 IOWR(p->BASE, 0x00, 0x002B);
		 IOWR(p->BASE, 0x01, Ypos>>8);
		 IOWR(p->BASE, 0x01, Ypos&0XFF);
	 IOWR(p->BASE, 0x00, 0x002C);
}

void lcd_clear(lcd_info *p, alt_u16 Color)
{
        alt_u32 index=0;
        lcd_set_cursor(p, 0x00,0x0000);
        IOWR(p->BASE, 0x00, 0x002C);
        for(index=0;index<76800;index++)
        {
        	IOWR(p->BASE, 0x01, Color);
        }
}

void lcd_draw_point(lcd_info *p, alt_u16 x,alt_u16 y,alt_u16 color )
{
        lcd_set_cursor(p, x,y);
        IOWR(p->BASE, 0x00, 0x002C);
        IOWR(p->BASE, 0x01, color);
}

lcd_info * lcd_init(alt_u32 BASE, alt_u32 RESET_N_BASE)
{
	lcd_info * p = malloc(sizeof(lcd_info));
	p->BASE = BASE;


	alt_u16 data1,data2;
		alt_u16 data3,data4;
		Set_LCD_RST;
		delay_ms(1);
		Clr_LCD_RST;
		delay_ms(10);       // Delay 10ms // This delay time is necessary
		Set_LCD_RST;
		delay_ms(120);       // Delay 120 ms




	IOWR(p->BASE, 0x00, 0x0011); //Exit Sleep
	IOWR(p->BASE, 0x00, 0x00CF);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0081);
		IOWR(p->BASE, 0x01, 0X00c0);

	IOWR(p->BASE, 0x00, 0x00ED);
		IOWR(p->BASE, 0x01, 0x0064);
		IOWR(p->BASE, 0x01, 0x0003);
		IOWR(p->BASE, 0x01, 0X0012);
		IOWR(p->BASE, 0x01, 0X0081);

	IOWR(p->BASE, 0x00, 0x00E8);
		IOWR(p->BASE, 0x01, 0x0085);
		IOWR(p->BASE, 0x01, 0x0001);
		IOWR(p->BASE, 0x01, 0x00798);

	IOWR(p->BASE, 0x00, 0x00CB);
		IOWR(p->BASE, 0x01, 0x0039);
		IOWR(p->BASE, 0x01, 0x002C);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0034);
		IOWR(p->BASE, 0x01, 0x0002);

	IOWR(p->BASE, 0x00, 0x00F7);
		IOWR(p->BASE, 0x01, 0x0020);

	IOWR(p->BASE, 0x00, 0x00EA);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0000);

	IOWR(p->BASE, 0x00, 0x00B1);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x001b);

	IOWR(p->BASE, 0x00, 0x00B6);
		IOWR(p->BASE, 0x01, 0x000A);
		IOWR(p->BASE, 0x01, 0x00A2);

	IOWR(p->BASE, 0x00, 0x00C0);    //Power control
		IOWR(p->BASE, 0x01, 0x0005);   //VRH[5:0]

	IOWR(p->BASE, 0x00, 0x00C1);    //Power control
		IOWR(p->BASE, 0x01, 0x0011);   //SAP[2:0];BT[3:0]

	IOWR(p->BASE, 0x00, 0x00C5);    //VCM control
		IOWR(p->BASE, 0x01, 0x0045);       //3F
		IOWR(p->BASE, 0x01, 0x0045);       //3C

	 IOWR(p->BASE, 0x00, 0x00C7);    //VCM control2
		 IOWR(p->BASE, 0x01, 0X00a2);

	IOWR(p->BASE, 0x00, 0x0036);    // Memory Access Control
		IOWR(p->BASE, 0x01, 0x0008);//48

	IOWR(p->BASE, 0x00, 0x00F2);    // 3Gamma Function Disable
		IOWR(p->BASE, 0x01, 0x0000);

	IOWR(p->BASE, 0x00, 0x0026);    //Gamma curve selected
		IOWR(p->BASE, 0x01, 0x0001);

	IOWR(p->BASE, 0x00, 0x00E0);    //Set Gamma
		IOWR(p->BASE, 0x01, 0x000F);
		IOWR(p->BASE, 0x01, 0x0026);
		IOWR(p->BASE, 0x01, 0x0024);
		IOWR(p->BASE, 0x01, 0x000b);
		IOWR(p->BASE, 0x01, 0x000E);
		IOWR(p->BASE, 0x01, 0x0008);
		IOWR(p->BASE, 0x01, 0x004b);
		IOWR(p->BASE, 0x01, 0X00a8);
		IOWR(p->BASE, 0x01, 0x003b);
		IOWR(p->BASE, 0x01, 0x000a);
		IOWR(p->BASE, 0x01, 0x0014);
		IOWR(p->BASE, 0x01, 0x0006);
		IOWR(p->BASE, 0x01, 0x0010);
		IOWR(p->BASE, 0x01, 0x0009);
		IOWR(p->BASE, 0x01, 0x0000);

	IOWR(p->BASE, 0x00, 0X00E1);    //Set Gamma
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x001c);
		IOWR(p->BASE, 0x01, 0x0020);
		IOWR(p->BASE, 0x01, 0x0004);
		IOWR(p->BASE, 0x01, 0x0010);
		IOWR(p->BASE, 0x01, 0x0008);
		IOWR(p->BASE, 0x01, 0x0034);
		IOWR(p->BASE, 0x01, 0x0047);
		IOWR(p->BASE, 0x01, 0x0044);
		IOWR(p->BASE, 0x01, 0x0005);
		IOWR(p->BASE, 0x01, 0x000b);
		IOWR(p->BASE, 0x01, 0x0009);
		IOWR(p->BASE, 0x01, 0x002f);
		IOWR(p->BASE, 0x01, 0x0036);
		IOWR(p->BASE, 0x01, 0x000f);

	IOWR(p->BASE, 0x00, 0x002A);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x00ef);

	 IOWR(p->BASE, 0x00, 0x002B);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0000);
		IOWR(p->BASE, 0x01, 0x0001);
		IOWR(p->BASE, 0x01, 0x003f);

	IOWR(p->BASE, 0x00, 0x003A);
		IOWR(p->BASE, 0x01, 0x0055);

	IOWR(p->BASE, 0x00, 0x00f6);
		IOWR(p->BASE, 0x01, 0x0001);
		IOWR(p->BASE, 0x01, 0x0030);
		IOWR(p->BASE, 0x01, 0x0000);

	IOWR(p->BASE, 0x00, 0x0029); //display on

	IOWR(p->BASE, 0x00, 0x002c);    // 0x2C

	return p;
}


void lcd_pattern_horizon(lcd_info *p)
{
        alt_u32 index=0;
        alt_u16  data=0;
        lcd_set_cursor(p, 0x00,0x0000);
        data=0x0000;
        for(index=0;index<240*80;index++)
        {
        	IOWR(p->BASE, 0x01, data);
        }
        lcd_set_cursor(p, 0x00,80);
        data=RED;
		for(index=0;index<240*80;index++)
		{
			IOWR(p->BASE, 0x01, data);
		}
	    lcd_set_cursor(p, 0x00,160);
		data=GREEN;
		for(index=0;index<240*80;index++)
		{
			IOWR(p->BASE, 0x01, data);
		}
		lcd_set_cursor(p, 0x00,240);
		data=BLUE;
		for(index=0;index<240*80;index++)
		{
			IOWR(p->BASE, 0x01, data);
		}
}

void lcd_pattern_vertical(lcd_info *p)
{
        int i,j,m;
        alt_u16  data=0;
        alt_u16  color[4]={WHITE,BLUE,GREEN,RED};
        lcd_set_cursor(p, 0x00,0x0000);
        for(m=0;m<320;m++)
        {
			for(i=0;i<4;i++)
			{
				data=color[i];
				for(j=0;j<60;j++)
				{
					IOWR(p->BASE, 0x01, data);
				}
			}
        }
}

