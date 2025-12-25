`timescale 1ns/1ps
module testbench;


	logic [7:0] A, B, S;
	logic [2:0] op;
	

	alu u_alu(
		.A	(A),
		.B	(B),
		.op	(op),
		.S	(S)
	);

	
	initial begin
		 
		op = 0; A = 0; B = 0;
		#10 A = 5; B = 8'hb; 
		#10 A = 8'hd; B = 7; op = 1;
		#100 $stop;
	end
endmodule