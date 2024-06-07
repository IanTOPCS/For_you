module tb_mul;
logic [1:0] sel;
logic [3:0] in;
logic ans;
mul fun(//combine with main code
	.sel(sel),
	.in(in),
	.ans(ans)
);
initial
begin//write the test data
	sel = 2'b00;
	in = 4'b0110;
	#10
	sel = 2'b01;
	in = 4'b0110;
	#10
	sel = 2'b10;
	in = 4'b0110;
	#10
	sel = 2'b11;
	in = 4'b0110;
end
initial
begin
	$monitor($time, "sel1=%b, sel2=%b, out=%b", sel[1], sel[0], ans);//output the ans of test data
end
endmodule