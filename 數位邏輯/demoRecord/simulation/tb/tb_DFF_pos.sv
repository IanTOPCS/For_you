module tb_DFF_pos;
logic data;
logic clk;
logic reset;
logic q;
//logic qbar;

DFF_pos fun(
	.data(data),
	.clk(clk),
	.reset(reset),
	.q(q)
	//.qbar(qbar)
);


always #10 clk = ~clk;

initial
begin
			clk = 0; reset = 0; data = 0;
	#100	reset = 0; data = 1;
	#100	reset = 1; data = 0;
	#100	reset = 1; data = 0;
	#100	$stop;
end

initial
begin
	$monitor($time, "clock = %b, reset = %b, data = %b, Q = %b", clk, reset, data, q);
end

endmodule
