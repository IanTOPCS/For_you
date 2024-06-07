module tb_accumulator_top;
logic clk;
logic reset;
logic [3:0]num;

accumulator_top f0(
	.clk(clk),
	.reset(reset),
	.out(num)
);

always #5 clk = ~clk;
initial begin
		 clk = 0; reset = 1;
	#10 reset = 0;
	#500 $stop;
end

endmodule 
