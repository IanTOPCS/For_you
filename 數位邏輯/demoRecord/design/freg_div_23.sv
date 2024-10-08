module freg_div_23(
	input clk, 
	input reset,
	output logic clk_out
);

	logic [31:0] q;
	
	always_ff @(posedge clk or posedge reset)
	begin
		if(reset)
			q <= 0;
		else
			q <= q + 1;
	end
	
	assign clk_out = q[23];
endmodule