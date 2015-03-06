
//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

module mtlhardware(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SW //////////
	SW,

	//////////// SDRAM //////////
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_DQM,
	DRAM_RAS_N,
	DRAM_WE_N,

	//////////// Accelerometer //////////
	G_SENSOR_CS_N,
	G_SENSOR_INT,
	I2C_SCLK,
	I2C_SDAT,

	//////////// 2x13 GPIO Header //////////
	GPIO_2,
	GPIO_2_IN,

	//////////// GPIO_1, GPIO_1 connect to MTL - Multi-Touch LCD Panel //////////
	MTL_B,
	MTL_DCLK,
	MTL_G,
	MTL_HSD,
	MTL_R,
	MTL_TOUCH_I2C_SCL,
	MTL_TOUCH_I2C_SDA,
	MTL_TOUCH_INT_n,
	MTL_VSD 
);

//=======================================================
//  PARAMETER declarations
//=======================================================


//=======================================================
//  PORT declarations
//=======================================================

//////////// CLOCK //////////
input 		          		CLOCK_50;

//////////// LED //////////
output		     [7:0]		LED;

//////////// KEY //////////
input 		     [1:0]		KEY;

//////////// SW //////////
input 		     [3:0]		SW;

//////////// SDRAM //////////
output		    [12:0]		DRAM_ADDR;
output		     [1:0]		DRAM_BA;
output		          		DRAM_CAS_N;
output		          		DRAM_CKE;
output		          		DRAM_CLK;
output		          		DRAM_CS_N;
inout 		    [15:0]		DRAM_DQ;
output		     [1:0]		DRAM_DQM;
output		          		DRAM_RAS_N;
output		          		DRAM_WE_N;

//////////// Accelerometer //////////
output		          		G_SENSOR_CS_N;
input 		          		G_SENSOR_INT;
output		          		I2C_SCLK;
inout 		          		I2C_SDAT;

//////////// 2x13 GPIO Header //////////
inout 		    [12:0]		GPIO_2;
input 		     [2:0]		GPIO_2_IN;

//////////// GPIO_1, GPIO_1 connect to MTL - Multi-Touch LCD Panel //////////
output		     [7:0]		MTL_B;
output		          		MTL_DCLK;
output		     [7:0]		MTL_G;
output		          		MTL_HSD;
output		     [7:0]		MTL_R;
output		          		MTL_TOUCH_I2C_SCL;
inout 		          		MTL_TOUCH_I2C_SDA;
input 		          		MTL_TOUCH_INT_n;
output		          		MTL_VSD;


//=======================================================
//  REG/WIRE declarations
//=======================================================

wire reset_n;
wire video_hs;
wire video_vs;
wire video_clk;
wire [7:0]	video_r;
wire [7:0]	video_g;
wire [7:0]	video_b;

assign {MTL_R,MTL_G,MTL_B} = {video_r, video_g, video_b};
assign MTL_DCLK = video_clk;
assign MTL_HSD = ~video_hs;
assign MTL_VSD = ~video_vs;

vga_pll vga_pll_inst(
	.areset(1'b0),
	.inclk0(CLOCK_50),
	.c0(video_clk),
	.locked(reset_n));

//=======================================================
//  Structural coding
//=======================================================

 mtlsopc u0 (
	  .clk_clk                                 (CLOCK_50),
	  .reset_reset_n                           (KEY[0]),
	  
	  
	  .altpll_areset_conduit_export            (),
	  .altpll_locked_conduit_export            (),
	  .altpll_phasedone_conduit_export         (),
	  
	  .altpll_sdram_clk                        (DRAM_CLK),
	  .sdram_wire_addr                         (DRAM_ADDR),
	  .sdram_wire_ba                           (DRAM_BA),
	  .sdram_wire_cas_n                        (DRAM_CAS_N),
	  .sdram_wire_cke                          (DRAM_CKE),
	  .sdram_wire_cs_n                         (DRAM_CS_N),
	  .sdram_wire_dq                           (DRAM_DQ),
	  .sdram_wire_dqm                          (DRAM_DQM),
	  .sdram_wire_ras_n                        (DRAM_RAS_N),
	  .sdram_wire_we_n                         (DRAM_WE_N),
	  
	  .alt_vip_itc_clocked_video_vid_clk       (video_clk),
	  .alt_vip_itc_clocked_video_vid_data      ({8'b0, video_r, video_g, video_b}),
	  .alt_vip_itc_clocked_video_underflow     (),
	  .alt_vip_itc_clocked_video_vid_datavalid (),
	  .alt_vip_itc_clocked_video_vid_v_sync    (video_vs),
	  .alt_vip_itc_clocked_video_vid_h_sync    (video_hs),
	  .alt_vip_itc_clocked_video_vid_f         (),
	  .alt_vip_itc_clocked_video_vid_h         (),
	  .alt_vip_itc_clocked_video_vid_v         (),
	  
	  .multi_touch_I2C_SDA                     (MTL_TOUCH_I2C_SDA),
     .multi_touch_I2C_SCL                     (MTL_TOUCH_I2C_SCL),
     .multi_touch_INT_n                       (MTL_TOUCH_INT_n)
	  
 );

 endmodule
