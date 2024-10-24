module BCD_show (
	input logic [3:0]A,
	input logic [3:0]B,
	input logic carry_in,
	output logic [6:0]seg,
	output logic output_carry,
	output logic carry_out
);

logic [3:0]tmp;
BCD first(
	.a(A),
	.b(B),
	.c(carry_in),
	.S(tmp),
	.output_carry(output_carry),
	.carry_out(carry_out)
);

seven_segment second(
	.in(tmp),
	.out(seg)
);

endmodule
