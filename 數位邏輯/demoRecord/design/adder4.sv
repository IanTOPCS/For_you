module adder4(
	input [3:0]A,
	input [3:0]B,
	output [3:0]S,
	output cout,
	input cin
);
logic [2:0]tmp;
add add1(//use full-adder to combine 4 bit adder
	.a(A[0]),
	.b(B[0]),
	.s(S[0]),
	.cin(cin),
	.cout(tmp[0])
);

add add2(
	.a(A[1]),
	.b(B[1]),
	.s(S[1]),
	.cin(tmp[0]),
	.cout(tmp[1])
);

add add3(
	.a(A[2]),
	.b(B[2]),
	.s(S[2]),
	.cin(tmp[1]),
	.cout(tmp[2])
);

add add4(
	.a(A[3]),
	.b(B[3]),
	.s(S[3]),
	.cin(tmp[2]),
	.cout(cout)
);
endmodule
