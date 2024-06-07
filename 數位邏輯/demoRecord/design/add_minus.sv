module add_minus(
	input [3:0]A,
	input [3:0]B,
	input m,
	output [3:0]S,
	output c,
	output v
);

logic [2:0]tmp;
logic [3:0]new_b;

xor(new_b[0], B[0], m);
add add1(//use full-adder to combine 4 bit adder
	.a(A[0]),
	.b(new_b[0]),
	.s(S[0]),
	.cin(m),
	.cout(tmp[0])
);
xor(new_b[1], B[1], m);
add add2(
	.a(A[1]),
	.b(new_b[1]),
	.s(S[1]),
	.cin(tmp[0]),
	.cout(tmp[1])
);
xor(new_b[2], B[2], m);
add add3(
	.a(A[2]),
	.b(new_b[2]),
	.s(S[2]),
	.cin(tmp[1]),
	.cout(tmp[2])
);
xor(new_b[3], B[3], m);
add add4(
	.a(A[3]),
	.b(new_b[3]),
	.s(S[3]),
	.cin(tmp[2]),
	.cout(c)
);
xor(v, c, tmp[2]);

endmodule
