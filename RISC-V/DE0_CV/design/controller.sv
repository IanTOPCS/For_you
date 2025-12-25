`include "mydefine.sv"
`timescale 1ns/100ps
module controller (
	input logic [6:0] funct7_, opcode_,
	input logic rst, clk,
	input logic [2:0] funct3_,
	input logic [31:0] rs1_value, rs2_value,
	output logic flush_IFID_, flush_IDEX_, rst_pc_, sel_pc_, write_regf_en_, sel_jump_, sel_alu_a_, write_ram_,
	output logic [1:0] sel_alu_b_, sel_rd_value_,
	output logic [3:0] op_
);
	logic BEQ_FLAG;
	logic BNE_FLAG;
	logic BLT_FLAG;
	logic BGE_FLAG;
	logic BLTU_FLAG;
	logic BGEU_FLAG;

	assign BEQ_FLAG = (rs1_value == rs2_value);
	assign BNE_FLAG = (rs1_value != rs2_value);
	assign BLT_FLAG = ($signed(rs1_value) < $signed(rs2_value));
	assign BGE_FLAG = ($signed(rs1_value) >= $signed(rs2_value));
	assign BLTU_FLAG = (rs1_value < rs2_value);
	assign BGEU_FLAG = (rs1_value >= rs2_value);

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
		sel_pc_ = 0;
		flush_IFID_ = 0;
		flush_IDEX_ = 0;
		write_regf_en_ = 0;
		sel_alu_b_ = 0;
		ns = ps;
		op_ = `ALUOP_ADD;
		sel_alu_a_ = 0;
		sel_jump_ = 0;
		sel_rd_value_ = 0;
		write_ram_ = 0;
		unique case (ps)
			s0: begin
				flush_IFID_ = 1;
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
				case (opcode_)
					`Opcode_I: begin
						unique case (funct3_)
							`F_ADDI: begin
								op_ = `ALUOP_ADD;
								write_regf_en_ = 1;
							end
							`F_SLTI: begin
								op_ = `ALUOP_LT;
								write_regf_en_ = 1;
							end
							`F_SLTIU: begin
								op_ = `ALUOP_LTU;
								write_regf_en_ = 1;
							end
							`F_ANDI: begin
								op_ = `ALUOP_AND;
								write_regf_en_ = 1;
							end
							`F_ORI: begin
								op_ = `ALUOP_OR;
								write_regf_en_ = 1;
							end
							`F_XORI: begin
								op_ = `ALUOP_XOR;
								write_regf_en_ = 1;
							end
							`F_SLLI: begin
								op_ = `ALUOP_SLL;
								write_regf_en_ = 1;
							end
							`F_SRLI_SRAI: begin
								unique case (funct7_)
									`F7_SRLI: begin
										op_ = `ALUOP_SRL;
										write_regf_en_ = 1;
									end
									`F7_SRAI: begin
										op_ = `ALUOP_SRA;
										write_regf_en_ = 1;
									end
								endcase
							end
						endcase
					end
					`Opcode_R_M: begin
						unique case (funct3_)
							`F_AND: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_AND;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// `F_REMU
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 3;
								end
							end
							`F_OR: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_OR;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// F_REM
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 3;
								end
							end
							`F_XOR: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_XOR;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// F_DIV
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 3;
								end
							end
							`F_ADD_SUB: begin
								unique case (funct7_)
									`F7_ADD: begin
										op_ = `ALUOP_ADD;
										write_regf_en_ = 1;
										sel_alu_b_ = 1;
									end
									`F7_SUB: begin
										op_ = `ALUOP_SUB;
										write_regf_en_ = 1;
										sel_alu_b_ = 1;
									end
									// MUL
									`F7_R_M: begin
										write_regf_en_ = 1;
										sel_rd_value_ = 2;
									end
								endcase
							end
							`F_SLT: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_LT;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// F_MULHSU
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 2;
								end
							end
							`F_SLTU: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_LTU;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// F_MULHU
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 2;
								end
							end
							`F_SLL: begin
								if (funct7_ == `F7_OPCODE_R) begin
									op_ = `ALUOP_SLL;
									write_regf_en_ = 1;
									sel_alu_b_ = 1;
								end
								// `F_MULH
								else if (funct7_ == `F7_R_M) begin
									write_regf_en_ = 1;
									sel_rd_value_ = 2;
								end
							end
							`F_SRL_SRA: begin
								unique case (funct7_)
									`F7_OPCODE_R: begin
										op_ = `ALUOP_SRL;  // SRL
										write_regf_en_ = 1;
										sel_alu_b_ = 1;
									end
									`F7_SRA: begin
										op_ = `ALUOP_SRA;  // SRA (if different funct7)
										write_regf_en_ = 1;
										sel_alu_b_ = 1;
									end
									// F_DIVU
									`F7_R_M: begin
										write_regf_en_ = 1;
										sel_rd_value_ = 3;
									end
								endcase
							end
						endcase
					end
					`Opcode_B: begin
						sel_jump_ = 1;
						unique case (funct3_)
							`F_BEQ: begin
								if (BEQ_FLAG) begin
									sel_pc_ = 1;
									flush_IDEX_ = 1;
									flush_IFID_ = 1;
								end
							end
							`F_BNE: begin
								if (BNE_FLAG) begin
									sel_pc_ = 1;
									flush_IDEX_ = 1;
									flush_IFID_ = 1;
								end
							end
							`F_BLT: begin
								if (BLT_FLAG) begin
									sel_pc_ = 1;
									flush_IFID_ = 1;
									flush_IDEX_ = 1;
								end
							end
							`F_BGE: begin
								if (BGE_FLAG) begin
									sel_pc_ = 1;
									flush_IDEX_ = 1;
									flush_IFID_ = 1;
								end
							end
							`F_BLTU: begin
								if (BLTU_FLAG) begin
									sel_pc_ = 1;
									flush_IDEX_ = 1;
									flush_IFID_ = 1;
								end
							end
							`F_BGEU: begin
								if (BGEU_FLAG) begin
									sel_pc_ = 1;
									flush_IDEX_ = 1;
									flush_IFID_ = 1;
								end
							end
						endcase
					end
					`Opcode_JAL: begin
						sel_pc_ = 1;
						flush_IFID_ = 1;
						flush_IDEX_ = 1;
						sel_alu_a_ = 1;
						sel_alu_b_ = 2;
						sel_jump_ = 1;
						op_ = `ALUOP_ADD;
						write_regf_en_ = 1;
					end
					`Opcode_JALR: begin
						sel_pc_ = 1;
						flush_IFID_ = 1;
						flush_IDEX_ = 1;
						sel_alu_a_ = 1;
						sel_alu_b_ = 2;
						sel_jump_ = 0;
						op_ = `ALUOP_ADD;
						write_regf_en_ = 1;
					end
					`Opcode_LUI: begin
						sel_alu_b_ = 0;
						op_ = `ALUOP_B;
						write_regf_en_ = 1;
					end
					`Opcode_AUIPC: begin
						sel_alu_a_ = 1;
						sel_alu_b_ = 0;
						op_ = `ALUOP_ADD;
						write_regf_en_ = 1;
					end
					`Opcode_L: begin
						unique case (funct3_)
							`F_LB: begin
								op_ = `ALUOP_ADD;
								sel_rd_value_ = 1;
								write_regf_en_ = 1;
							end
							`F_LH: begin
								op_ = `ALUOP_ADD;
								sel_rd_value_ = 1;
								write_regf_en_ = 1;
							end
							`F_LW: begin
								op_ = `ALUOP_ADD;
								sel_rd_value_ = 1;
								write_regf_en_ = 1;
							end
							`F_LBU: begin
								op_ = `ALUOP_ADD;
								sel_rd_value_ = 1;
								write_regf_en_ = 1;
							end
							`F_LHU: begin
								op_ = `ALUOP_ADD;
								sel_rd_value_ = 1;
								write_regf_en_ = 1;
							end
						endcase
					end
					`Opcode_S: begin
						unique case (funct3_)
							`F_SB: begin
								op_ = `ALUOP_ADD;
								write_ram_ = 1;
							end
							`F_SH: begin
								op_ = `ALUOP_ADD;
								write_ram_ = 1;
							end
							`F_SW: begin
								op_ = `ALUOP_ADD;
								write_ram_ = 1;
							end
						endcase
					end
				endcase
			end
		endcase
	end
endmodule