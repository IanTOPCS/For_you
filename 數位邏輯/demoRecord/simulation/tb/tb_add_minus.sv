module tb_add_minus;
logic [3:0]A;
logic [3:0]B;
logic m;
logic [3:0]S;
logic c;
logic v;

add_minus fun(
	.A(A),
	.B(B),
	.m(m),
	.S(S),
	.c(c),
	.v(v)
);

initial
begin
	A=4'b1111; B=4'b1111; m=0;
	#10 A=4'b0100; B=4'b0111; m=0;
	#10 A=4'b0000; B=4'b1111; m=1;
	#10 A=4'b1101; B=4'b1010; m=1;
	#10 A=4'b0111; B=4'b1000; m=1;
	#10 $stop;
end

initial
begin
	$monitor($time, " a=%b, b=%b, m=%b, C=%b, s=%b, v=%b", A, B, m, c, S, v);
end

endmodule
