module tb_seven_segment;

logic [3:0]in;
logic [6:0]out;

seven_segment fun(
	.in(in),
	.out(out)
);

initial
begin
	in = 4'b0000;
	#10
	in = 4'b0001;
	#10
	in = 4'b0010;
	#10
	in = 4'b0011;
	#10
	in = 4'b0100;
	#10
	in = 4'b0101;
	#10
	in = 4'b0110;
	#10
	in = 4'b0111;
	#10
	in = 4'b1000;
	#10
	in = 4'b1001;
	#10
	in = 4'b1010;
	#10
	in = 4'b1011;
	#10
	in = 4'b1100;
	#10
	in = 4'b1101;
	#10
	in = 4'b1110;
	#10
	in = 4'b1111;
	#10 $stop;
end

initial
begin
	$monitor($time, "in = %b, output = %b", in, out);
end

endmodule
