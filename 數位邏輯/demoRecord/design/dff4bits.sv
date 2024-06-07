module dff4bits(
	input clk, reset,
	input [3:0]in,
	output logic [3:0]out
);

DFF_pos f0(
	.data(in[3]),
	.reset(reset),
	.clk(clk),
	.q(out[3])
);

DFF_pos f1(
	.data(in[2]),
	.reset(reset),
	.clk(clk),
	.q(out[2])
);

DFF_pos f2(
	.data(in[1]),
	.reset(reset),
	.clk(clk),
	.q(out[1])
);

DFF_pos f3(
	.data(in[0]),
	.reset(reset),
	.clk(clk),
	.q(out[0])
);

endmodule
