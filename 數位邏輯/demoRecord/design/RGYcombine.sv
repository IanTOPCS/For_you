module RGYcombine(
	input clk,
	input reset,
	output logic [1:0]r, g, y
);

logic [3:0]q;

fourupdown f0(
	.clk(clk),
	.reset(reset),
	.x(1'b0),
	.q(q)
);

assign r[0] = (~q[3]);
assign r[1] = q[3];
assign g[0] = (q[3]&(~q[2]))|(q[3]&(~q[1]));
assign g[1] = ((~q[3])&(~q[2]))|((~q[3])&(~q[1]));
assign y[0] = (q[3]&q[2]&q[1]);
assign y[1] = ((~q[3])&q[2]&q[1]);

endmodule
