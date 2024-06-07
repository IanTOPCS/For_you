module tb_student_num;

logic clk, reset;
logic [3:0]id;

student_num f0(
	.clk(clk),
	.reset(reset),
	.id(id)
);

always #5 clk = ~clk;
initial begin
		 clk = 0; reset = 1;
	#10 reset = 0;
	#500 $stop;
end

endmodule
