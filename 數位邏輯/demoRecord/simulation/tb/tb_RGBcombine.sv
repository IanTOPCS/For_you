module tb_RGBcombine;

logic clk, reset;
logic [1:0] r, y, g;
RGYcombine f0(
	.clk(clk),
	.reset(reset),
	.r(r),
	.y(y),
	.g(g)
);
always #5 clk = ~clk;

initial begin
		clk = 0; reset = 1;
	#10 reset = 0;
	#200 $stop;
end

endmodule
