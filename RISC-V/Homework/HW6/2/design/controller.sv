module controller (
	input logic [6:0] funct7_, opcode_,
	input logic rst, clk,
	input logic [2:0] funct3_,
	output logic flush_IFID_, flush_IDEX_, rst_pc_, sel_pc
);
	typedef enum {s0, s1, s2} fsm_state;
	fsm_state ps, ns;
	
	always_ff @(posedge clk) begin
		if (rst) begin
			ps <= #1 s0;
		end
		else begin
			ps <= #1 ns;
		end
	end
	
	always_comb begin
		rst_pc_ = 0;
		sel_pc = 0;
		flush_IFID_ = 0;
		flush_IDEX_ = 0;
		ns = ps;
		unique case (ps)
			s0: begin
				// flush_IFID_ = 1;
				flush_IDEX_ = 1;
				rst_pc_ = 1;
				ns = s1;
			end
			s1: begin
				flush_IFID_ = 1;
				flush_IDEX_ = 1;
				rst_pc_ = 1;
				ns = s2;
			end
			s2: begin
			end
		endcase
	end
endmodule