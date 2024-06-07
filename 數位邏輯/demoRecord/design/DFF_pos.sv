module DFF_pos(
	input logic data,
	input logic reset,
	input logic clk,
	output logic q

);

always_ff @(posedge clk)
	begin
		if(reset)
			begin
				q <= 1'b0;
				
			end
		else
			begin
				q <= data;
				
			end
	end
endmodule
