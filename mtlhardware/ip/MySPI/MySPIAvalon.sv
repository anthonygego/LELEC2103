module MySPIAvalon(
	// Avalon bus
	input  logic        clk,
	input  logic        reset,
	input  logic  [1:0] address,
	input  logic        write,
	input  logic        read,
	input  logic [31:0] writedata,
	output logic [31:0] readdata,
    // Export
    input  logic        SCK, 
    input  logic        CS_N,
    input  logic        MOSI,
	output logic        MISO
	);

/*---------------------------------------------------------------------------*/
/* Register file                                                             */
/*---------------------------------------------------------------------------*/
logic [7:0] TxData, RxData, TxStatus, RxStatus;

// Logic for writes
always_ff @(posedge clk, posedge reset)
begin
	if (reset) begin
		RxData <= 8'b0;
		RxStatus <= 1'b0;
	end else if (write && (address == 1))
		RxData <= writedata[7:0];
	else if (write && (address == 3))
		RxStatus <= writedata[7:0];
end

// Logic for reads
always_comb
begin
	if (read && (address==0))
		readdata = {24'b0, TxData}; 
	else if (read && (address==1))
		readdata = {24'b0, RxData}; 
    else if (read && (address==2))
		readdata = {24'b0, TxStatus};
    else if (read && (address==3))
		readdata = {24'b0, RxStatus};
	else
		readdata = {32'bz};
end

/*---------------------------------------------------------------------------*/
/* SPI unit                                                                  */
/*---------------------------------------------------------------------------*/

MySPI MySPI0 (clk, reset, SCK, CS_N, MOSI, MISO, TxData, TxStatus, RxData, RxStatus);

endmodule
