module ten_digit(
	input clk, reset, c_in,
	output logic [2:0]q,
	output logic carry_out
);

logic a, b, c, da, db, dc;

assign da = ((~c_in)&a)|(a&(~c))|(c_in&c&b);
DFF_pos f0(
	.data(da),
	.reset(reset),
	.clk(clk),
	.q(a)
);

assign db = ((~c_in)&b)|(b&(~c))|(c_in&(~a)&(~b)&c);
DFF_pos f1(
	.data(db),
	.reset(reset),
	.clk(clk),
	.q(b)
);

assign dc = ((~c_in)&c)|(c_in&(~c));
DFF_pos f2(
	.data(dc),
	.reset(reset),
	.clk(clk),
	.q(c)
);

assign carry_out = (c_in&a&c);
assign q[2:0] = {a, b, c};

endmodule
