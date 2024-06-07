module tb_fourBitCNT;

logic clk, reset;
logic [3:0]counter;

fourBitCNT fun(
	.clk(clk),
	.reset(reset),
	.counter(counter)
);

always #5 clk = ~clk;

initial
begin
	clk = 0;
	reset = 1;
	#10 reset = 0;
	#500 $stop;
end

endmodule
