module unit_digit(
	input clk, reset, c_in,
	output logic [3:0]q,
	output logic carry_out
);

logic a, b, c, d, da, db, dc, dd;

assign da = ((~c_in)&a)|(a&(~d))|((c_in)&b&c&d);
DFF_pos f0(
	.data(da),
	.reset(reset),
	.clk(clk),
	.q(a)
);

assign db = ((~c_in)&b)|(b&(~c))|(b&(~d))|(c_in&(~b)&c&d);
DFF_pos f1(
	.data(db),
	.reset(reset),
	.clk(clk),
	.q(b)
);

assign dc = ((~c_in)&c)|(c&(~d))|(c_in&(~a)&(~c)&d);
DFF_pos f2(
	.data(dc),
	.reset(reset),
	.clk(clk),
	.q(c)
);

assign dd = ((~c_in)&d)|(c_in&(~d));
DFF_pos f3(
	.data(dd),
	.reset(reset),
	.clk(clk),
	.q(d)
);

assign carry_out = (c_in&a&d);
assign q[3:0] = {a, b, c, d};

endmodule
