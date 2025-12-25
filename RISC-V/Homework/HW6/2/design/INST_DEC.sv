module INST_DEC (
	input logic [31:0] inst_r,
	output logic [6:0] funct7_, opcode_,
	output logic [4:0] addr_rs1_, addr_rs2_, addr_rd_,
	output logic [2:0] funct3_,
	output logic [31:0] imm_
);
	assign opcode_ = inst_r[6:0];
	assign addr_rd_ = inst_r[11:7];
	assign funct3_ = inst_r[14:12];
	assign addr_rs1_ = inst_r[19:15];
	assign addr_rs2_ = inst_r[24:20];
	assign funct7_ = inst_r[31:25];
	assign imm_ = {{20{inst_r[31]}}, inst_r[31:20]};
	
endmodule