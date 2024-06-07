module tb_add;
logic a;
logic b;
logic cin;
logic s;
logic cout;
add fun(//combine full-adder to testbench
	.a(a),
	.b(b),
	.cin(cin),
	.s(s),
	.cout(cout)
);
initial//write the test data of full-adder
begin
	a = 0; b = 0; cin = 0;
	#10 a = 0; b = 0; cin = 1;
	#10 a = 0; b = 1; cin = 0;
	#10 a = 0; b = 1; cin = 1;
	#10 a = 1; b = 0; cin = 0;
	#10 a = 1; b = 0; cin = 0;
	#10 a = 1; b = 0; cin = 1;
	#10 a = 1; b = 1; cin = 0;
	#10 a = 1; b = 1; cin = 1;
	#10 $stop;
end
initial
begin//show the ans on moniter
	$monitor($time, "a = %b, b = %b, cin = %b, s = %b, cout = %b", a, b, cin, s, cout);
end
endmodule
