module threeBitCNT(
	input  clk,
	input  reset,
	output logic [2:0]counter,
	output logic y
);

logic a, b, c, da, db, dc;
//logic an, bn, cn;
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

assign da = (a&(~c))|(c&(a^b));
assign db = (b^c);
assign dc = (~c);
assign y = (a&b&c);
assign counter[2:0] = {a, b, c};

endmodule
