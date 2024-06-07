module BCD(
	input logic [3:0]a,
	input logic [3:0]b,
	input logic c,
	output logic [3:0]S,
	output logic output_carry,
	output logic carry_out
);


logic tmp_c;
logic [3:0]tmp_S;
adder4 first(
	.A(a),
	.B(b),
	.S(tmp_S),
	.cout(tmp_c),
	.cin(c)
);

logic [3:0]second_in;
assign second_in[3] = 1'b0;
assign second_in[0] = second_in[3];
assign second_in[2] = ((tmp_S[3]&tmp_S[2])|(tmp_S[3]&tmp_S[1])|tmp_c);
assign second_in[1] = second_in[2];
assign output_carry = second_in[2];
assign carry_out = tmp_c;
logic trash;
adder4 second(
	.A(tmp_S),
	.B(second_in),
	.cin(1'b0),
	.cout(trash),
	.S(S)
);

endmodule
