module tb_threeBitCNT;

logic clk;
logic reset;
logic [2:0]counter;
logic y;

threeBitCNT fun(
	.clk(clk),
	.reset(reset),
	.counter(counter),
	.y(y)
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
