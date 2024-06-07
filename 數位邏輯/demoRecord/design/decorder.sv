module decorder(
	input [2:0] in,//input
	output logic [7:0] f//output
);
always_comb
	begin
		case(in)//use the input to search the output which is the answer.
			3'b000: f = 8'b10000000;
			3'b001: f = 8'b01000000;
			3'b010: f = 8'b00100000;
			3'b011: f = 8'b00010000;
			3'b100: f = 8'b00001000;
			3'b101: f = 8'b00000100;
			3'b110: f = 8'b00000010;
			3'b111: f = 8'b00000001;
			default: f = 8'b00000000;
		endcase
	end
	
endmodule