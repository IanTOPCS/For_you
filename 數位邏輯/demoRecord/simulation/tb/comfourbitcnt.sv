module comfourbitcnt(
	input clk,
	input reset,
	output logic [6:0]seg
);

logic [3:0]in;

fourBitCNT fun(
	.clk(clk),
	.counter(in),
	.reset(reset)
);

seven_segment funa(
	.in(in),
	.out(seg)
);

endmodule
