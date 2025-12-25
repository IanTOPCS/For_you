`include "mydefine.sv"
module INST_DEC (
	input logic [31:0] inst_r,
	output logic [6:0] funct7_, opcode_,
	output logic [4:0] addr_rs1_, addr_rs2_, addr_rd_,
	output logic [2:0] funct3_,
	output logic [31:0] imm_
);
	assign opcode_ = inst_r[6:0];
	assign funct3_ = inst_r[14:12];
	assign addr_rd_ = inst_r[11:7];
	assign addr_rs1_ = inst_r[19:15];
	assign addr_rs2_ = inst_r[24:20];
	assign funct7_ = inst_r[31:25];
	
	logic [31:0] IMM_I;
	logic [31:0] IMM_B;
	logic [31:0] IMM_JAL;
	logic [31:0] IMM_LUI_AUIPC;
	logic [31:0] IMM_S;
	assign IMM_I = {{20{inst_r[31]}}, inst_r[31:20]};
	assign IMM_B = {{20{inst_r[31]}}, inst_r[7], inst_r[30:25], inst_r[11:8], 1'b0};
	assign IMM_JAL = {{12{inst_r[31]}}, inst_r[19:12], inst_r[20], inst_r[30:21], 1'b0};
	assign IMM_LUI_AUIPC = {inst_r[31:12], 12'b0};
	assign IMM_S = {{20{inst_r[31]}}, inst_r[31:25], inst_r[11:7]};

	always_comb begin
		unique case (opcode_)
			`Opcode_I: imm_ = IMM_I;
			`Opcode_B: imm_ = IMM_B;
			`Opcode_JAL: imm_ = IMM_JAL;
			`Opcode_JALR: imm_ = IMM_I;
			`Opcode_LUI: imm_ = IMM_LUI_AUIPC;
			`Opcode_AUIPC: imm_ = IMM_LUI_AUIPC;
			`Opcode_L: imm_ = IMM_I;
			`Opcode_S: imm_ = IMM_S;
		endcase
	end
	
endmodule