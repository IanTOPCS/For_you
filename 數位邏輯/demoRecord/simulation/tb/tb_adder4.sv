module tb_adder4;
logic [3:0]A;//the input of a
logic [3:0]B;//the input of b
logic [3:0]S;//the output of sum
logic cout;//the output of cout
logic cin;//the input of cin

adder4 fun(//combine the 4adder to testbench
	.A(A),
	.B(B),
	.S(S),
	.cout(cout),
	.cin(cin)
);
initial
begin
	A=4'b0111; B = 4'b0110; cin = 0;
	#10
	A=4'b1000; B = 4'b1001; cin = 0;
	#10
	A=4'b1100; B = 4'b1000; cin=1;
	#10
	A=4'b0101; B = 4'b1010; cin = 1;
	#10
	A = 4'b0000; B = 4'b0001; cin = 1;
	#10 $stop;
end
initial
begin
	$monitor($time, "A=%b, B=%b, cin=%b, S=%b, cout=%b", A, B, cin, S, cout);
end
endmodule
