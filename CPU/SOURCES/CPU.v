module CPU_TOP( clk, addr, data );
	input clk;
	inout [31:0]addr;
	inout [31:0]data;
	
	CPU U0( .clk(clk), .addr(addr), .data(data) );
	
endmodule

module CPU( clk, addr, data );
	input clk;
	inout [31:0]addr;
	inout [31:0]data;

	Control_Center U0( .clk(clk), .indat(data), .outdat(data));
	ALU U1( .clk(clk), .indat(data), .outdat(data) );
	RAM U2( .clk(clk), .addr(addr), .data(data) );
	ROM U3( .clk(clk), .addr(addr), .data(data) );
	
endmodule
