module fourBitCNT(
	input clk, 
	input reset,
	output logic [3:0]counter
);

logic a, b, c, d, da, db, dc, dd;

DFF_pos funa(
	.data(da),
	.reset(reset),
	.clk(clk),
	.q(a)
);

DFF_pos funb(
	.data(db),
	.reset(reset),
	.clk(clk),
	.q(b)
);

DFF_pos func(
	.data(dc),
	.reset(reset),
	.clk(clk),
	.q(c)
);

DFF_pos fund(
	.data(dd),
	.reset(reset),
	.clk(clk),
	.q(d)
);

assign da = ((~a)&b&c&d)|(a&(~c))|(a&(~d))|(a&(~b));
assign db = (b&(~c))|(b&(~d))|((~b)&c&d);
assign dc = (c^d);
assign dd = (~d);
assign counter[3:0] = {a, b, c, d};

endmodule
