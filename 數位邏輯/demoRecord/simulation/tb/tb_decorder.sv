module tb_decorder;
logic [2:0]in;
logic [7:0]out;
new_decorder fun(
	.in(in),
	.f(out)
);
initial
begin
	in = 3'b000;
	#10
	in = 3'b001;
	#10
	in = 3'b010;
	#10
	in = 3'b011;
	#10
	in = 3'b100;
	#10
	in = 3'b101;
	#10
	in = 3'b110;
	#10
	in = 3'b111;
	#10 $stop;
end

initial
begin
	$monitor($time, "A=%b, B=%b, C=%b, out=%b", in[2], in[1], in[0], out);
end
endmodule