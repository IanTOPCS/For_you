module tb_fourupdown;

logic clk, reset, x;
logic [3:0]q;

fourupdown f0(
	.clk(clk),
	.reset(reset),
	.x(x),
	.q(q)
);
always #5 clk = ~clk;

initial begin
		clk = 0; reset = 1; x = 0;
	#10 reset = 0;
	#200 x = 1;
	#200 $stop;

end

endmodule
