module MySPI (
    input  logic       clk, reset,
    input  logic       MySPI_clk, MySPI_cs, MySPI_sdi,
    output logic       MySPI_sdo,
    output logic [7:0] TxData, TxStatus,
    input  logic [7:0] RxData, RxStatus
);

//--- Registers Address ---------------------------------

parameter A_TxData              = 7'h00;
parameter A_RxData              = 7'h01;
parameter A_TxStatus            = 7'h02;
parameter A_RxStatus            = 7'h03;

//--- FSM States ----------------------------------------

typedef enum logic [3:0] {
    S_Wait, 
    S_Addr, S_Addr_00, S_Addr_01, S_Addr_11,
    S_Data, S_Data_00, S_Data_01, S_Data_11,
    S_End} statetype;

//--- Declarations --------------------------------------

statetype       SPI_state, SPI_nextstate;
logic           SPI_CLK0, SPI_CLK;
logic           SPI_CS0, SPI_CS;
logic [2:0]     SPI_counter;
logic           SPI_counter_reset, SPI_counter_inc;  
logic [7:0]     SPI_address, SPI_data;
logic           SPI_address_shift;
logic           SPI_data_shift, SPI_data_load, SPI_data_update;

//--- SPI Output ----------------------------------------

assign MySPI_sdo = SPI_data[7];

//--- SPI Double Synchronization ------------------------

always @ (posedge clk)
begin
    SPI_CLK0 <= MySPI_clk;  SPI_CLK  <= SPI_CLK0;
    SPI_CS0  <= MySPI_cs;   SPI_CS   <= SPI_CS0;
end


//--- SPI FSM -------------------------------------------

always_ff @ (posedge clk)
    SPI_state <= SPI_nextstate;
    
always_comb
begin
    SPI_nextstate = SPI_state;
    case (SPI_state)
        S_Wait   : if (SPI_CS) SPI_nextstate = S_Wait;
                            else SPI_nextstate = S_Addr;
        S_Addr   : SPI_nextstate = S_Addr_00;
        S_Addr_00 : if (SPI_CLK) SPI_nextstate = S_Addr_01;
        S_Addr_01 : SPI_nextstate = S_Addr_11;
        S_Addr_11 : if (SPI_CLK) SPI_nextstate = S_Addr_11;
                            else if (SPI_counter == 3'b000) SPI_nextstate = S_Data;
                            else SPI_nextstate = S_Addr_00;
        S_Data   : SPI_nextstate = S_Data_00;
        S_Data_00 : if (SPI_CLK) SPI_nextstate = S_Data_01;
        S_Data_01 : SPI_nextstate = S_Data_11;
        S_Data_11 : if (SPI_CLK) SPI_nextstate = S_Data_11;
                            else if (SPI_counter == 3'b000) SPI_nextstate = S_End;
                            else SPI_nextstate = S_Data_00;
        S_End     : SPI_nextstate = S_Wait;
    endcase
    if (SPI_CS) SPI_nextstate = S_Wait;
end

assign SPI_counter_reset = ((SPI_state == S_Addr) | (SPI_state == S_Data));
assign SPI_counter_inc   = ((SPI_state == S_Addr_01) | (SPI_state == S_Data_01));
assign SPI_address_shift = (SPI_state == S_Addr_01);
assign SPI_data_shift    = (SPI_state == S_Data_01);
assign SPI_data_load     = (SPI_state == S_Data);
assign SPI_data_update   = ((SPI_state == S_End) & SPI_address[7]);

//--- On the positive edge of the clock -----------------

always_ff @ (posedge clk)
begin
    
    if (SPI_counter_reset) SPI_counter <= 3'b000;
		else if (SPI_counter_inc) SPI_counter <= SPI_counter + 3'b1;
		
	if (SPI_address_shift) SPI_address <= { SPI_address[6:0], MySPI_sdi };
	
	if (SPI_data_shift) SPI_data <= { SPI_data[6:0], MySPI_sdi };
    else if (SPI_data_load)
        case (SPI_address[6:0])
            A_RxData            : SPI_data <= RxData;
            A_RxStatus          : SPI_data <= RxStatus;
        endcase
        
    if (reset) TxData <= 8'b0;
    else if ((SPI_data_update) & (SPI_address[6:0] == A_TxData)) TxData <= SPI_data; 
    
    if(reset) TxStatus  <= 1'b0;
    else if ((SPI_data_update) & (SPI_address[6:0] == A_TxStatus)) TxStatus <= SPI_data;
    
end

endmodule
