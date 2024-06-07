module add(
	input a,
	input b,
	input cin,
	output s,
	output cout
);
logic hs;//half adder sum is a xor b
xor(hs, a, b);
logic hc;//half adder carry 
and(hc, a, b);
xor (s, hs, cin);//sum of full_adder
logic fc;
and(fc, hs, cin);//anothe half adder carry
or(cout, fc, hc);//add together two carry to compute the cout
endmodule
