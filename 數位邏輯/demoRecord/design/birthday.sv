module birthday(
	input clk, reset,
	output logic [3:0]id
);

logic a, b, c, d, da, db, dc, dd;

assign da = ((~a) & (~d))|((~a) & (~c));
DFF_pos f0(
	.data(da),
	.reset(reset),
	.clk(clk),
	.q(a)
);

assign db = ((~a) & (~c) & d)|((~a) & c & (~d));
DFF_pos f1(
	.data(db),
	.reset(reset),
	.clk(clk),
	.q(b)
);

assign dc = ((~c) & (d))|(a & d)|((~a) & c & (~d));
DFF_pos f2(
	.data(dc),
	.reset(reset),
	.clk(clk),
	.q(c)
);

assign dd = (~c)|((~a) & d);
DFF_pos f3(
	.data(dd),
	.reset(reset),
	.clk(clk),
	.q(d)
);

assign id[3:0] = {a, b, c, d};

endmodule
