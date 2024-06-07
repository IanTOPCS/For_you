module accumulator_top(
	output logic [3:0]out,
	input clk, reset
);

logic [3:0]last;
logic [3:0]num;
logic [3:0]tmp;
student_num f0(
	.clk(clk),
	.reset(reset),
	.id(num)
);

logic trash;
adder4 f1(
	.A(num),
	.B(last),
	.S(tmp),
	.cout(trash),
	.cin(1'b0)
);

dff4bits f2(
	.clk(clk),
	.reset(reset),
	.in(tmp),
	.out(last)
);

assign out = tmp;

endmodule
