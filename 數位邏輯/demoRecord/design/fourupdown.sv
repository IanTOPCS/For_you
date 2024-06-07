module fourupdown(
	input x,
	input clk,
	input reset,
	output logic [3:0]q
);

logic a, b, c, d, da, db, dc, dd;

assign da = ((~x)&a&(~b))|(a&b&(~d))|(a&b&(~c))|(x&a&d)|((~x)&(~a)&b&c&d)|(x&(~a)&(~b)&(~c)&(~d));

DFF_pos f0(
	.data(da),
	.reset(reset),
	.clk(clk),
	.q(a)
);

assign db = ((~x)&b&(~c))|(b&c&(~d))|(x&b&d)|((~x)&(~b)&c&d)|(x&(~b)&(~c)&(~d));

DFF_pos f1(
	.data(db),
	.reset(reset),
	.clk(clk),
	.q(b)
);

assign dc = ((~c)&(~x)&d)|((~x)&c&(~d))|(x&(~c)&(~d))|(x&c&d);

DFF_pos f2(
	.data(dc),
	.reset(reset),
	.clk(clk),
	.q(c)
);

assign dd = (~d);

DFF_pos f3(
	.data(dd),
	.reset(reset),
	.clk(clk),
	.q(d)
);

assign q[3:0] = {a, b, c, d};

endmodule
