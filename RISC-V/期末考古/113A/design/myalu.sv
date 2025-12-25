`include "mydefine.sv"
module myalu (
	input logic [3:0] op,
	input logic [31:0] alu_a,
	input logic [31:0] alu_b,
	output logic [31:0] alu_out
);
	always_comb begin
		unique case (op)
			`ALUOP_ADD : alu_out = alu_a + alu_b;
			`ALUOP_SUB : alu_out = $signed(alu_a) - $signed(alu_b);
			`ALUOP_AND : alu_out = alu_a & alu_b;
			`ALUOP_OR : alu_out = alu_a | alu_b;
			`ALUOP_XOR : alu_out = alu_a ^ alu_b;
			`ALUOP_A : alu_out = alu_a;
			`ALUOP_A_ADD_4 : alu_out = alu_a + 4;
			`ALUOP_LTU : alu_out = alu_a < alu_b;
			`ALUOP_LT : alu_out = $signed(alu_a) < $signed(alu_b);
			`ALUOP_SLL : alu_out = alu_a << alu_b[4:0];
			`ALUOP_SRL : alu_out = alu_a >> alu_b[4:0];
			`ALUOP_SRA : alu_out = $signed(alu_a) >>> alu_b[4:0];
			`ALUOP_B : alu_out = alu_b;
			default : alu_out = alu_a;
		endcase
	end
endmodule