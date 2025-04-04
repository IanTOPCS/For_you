module hour_timer(
	input clk, reset,
	output logic [2:0] sec_tens, min_tens,
	output logic [3:0] sec_units, min_units
);

logic sec_units_carry, min_units_carry, sec_tens_carry, min_tens_carry;

unit_digit f0(
	.clk(clk),
	.reset(reset),
	.c_in(1'b1),
	.q(sec_units),
	.carry_out(sec_units_carry)
);

ten_digit f1(
	.clk(clk),
	.reset(reset),
	.c_in(sec_units_carry),
	.q(sec_tens),
	.carry_out(sec_tens_carry)
);

unit_digit f2(
	.clk(clk),
	.reset(reset),
	.c_in(sec_tens_carry),
	.q(min_units),
	.carry_out(min_units_carry)
);

ten_digit f3(
	.clk(clk),
	.reset(reset),
	.c_in(min_units_carry),
	.q(min_tens),
	.carry_out(min_tens_carry)
);

endmodule
