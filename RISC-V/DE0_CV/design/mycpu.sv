`include "mydefine.sv"
module mycpu(
	input logic clk, rst,
	output logic [31:0] regs_31
);
	// progrom-counter
	logic rst_pc_, sel_pc_r;
	logic [31:0] pc,pc_next, pc_r, pc_rr, jump_addr_;
	always_comb begin
		case (sel_pc_r)
			1'd0: begin
				pc_next = pc + 4;
			end
			1'd1: begin
				pc_next = jump_addr_;
			end
		endcase
	end
	always_ff @(posedge clk) begin
		if (rst|rst_pc_) begin
			pc <= 0;
		end
		else begin
			pc <= pc_next;
		end
	end
	
	logic [31:0] inst_;
	// promgram rom
	Program_Rom myprogram_rom (
		// in
		.Rom_addr (pc),
		// out
		.Rom_data (inst_)
	);
	
	// pipe 1 IF_ID
	logic flush_IFID_r, flush_IFID_;
	logic [31:0] inst_r;
	assign rst_or_flush_IFID_r = rst | flush_IFID_r;
	always_ff @(posedge clk) begin
		if (rst_or_flush_IFID_r) begin
			inst_r <= `I_NOP;
			pc_r <= 0;
		end
		else begin
			inst_r <= inst_;
			pc_r <= pc;
		end
	end
	
	// INST_DEC
	logic [6:0] funct7_, opcode_;
	logic [4:0] addr_rs1_, addr_rs2_, addr_rd_;
	logic [2:0] funct3_, funct3_r;
	logic [31:0] imm_;
	INST_DEC myinst_dec (
		.inst_r (inst_r),
		.funct7_ (funct7_),
		.opcode_ (opcode_),
		.addr_rs1_ (addr_rs1_),
		.addr_rs2_ (addr_rs2_),
		.addr_rd_ (addr_rd_),
		.funct3_ (funct3_),
		.imm_ (imm_)
	);
	
	// Reg file
	logic write_regf_en_r, sel_rs1_value_, sel_rs2_value_;
	logic [4:0] addr_rd_r;
	logic [31:0] rd_value_, rs1_value, rs2_value, rs1_value_, rs2_value_, alu_out;
	Reg_file myreg (
		.clk (clk),
		.rst (rst),
		.write_regf_en (write_regf_en_r),
		.addr_rd (addr_rd_r),
		.addr_rs1 (addr_rs1_),
		.addr_rs2 (addr_rs2_),
		.rd_value (rd_value_),
		.rs1_value (rs1_value),
		.rs2_value (rs2_value),
		.regs_31 (regs_31)
	);
	logic flush_IDEX_;
	// controller
	logic sel_pc_, sel_alu_a_r, sel_jump_, sel_jump_r, sel_alu_a_, write_ram_, write_ram_r;
	logic [1:0] sel_rd_value_, sel_rd_value_r;
	logic [1:0] sel_alu_b_r, sel_alu_b_;
	logic [3:0] op_, op_r;
	logic write_regf_en_;
	controller mycontroller(
		// in
		.funct7_ (funct7_),
		.funct3_ (funct3_),
		.opcode_ (opcode_),
		.rst (rst),
		.clk (clk),
		.rs1_value (rs1_value_),
		.rs2_value (rs2_value_),
		// out
		.sel_alu_b_ (sel_alu_b_),
		.write_regf_en_ (write_regf_en_),
		.flush_IFID_ (flush_IFID_),
		.flush_IDEX_ (flush_IDEX_),
		.rst_pc_ (rst_pc_),
		.sel_pc_ (sel_pc_),
		.op_ (op_),
		.sel_jump_ (sel_jump_),
		.sel_alu_a_ (sel_alu_a_),
		.write_ram_ (write_ram_),
		.sel_rd_value_ (sel_rd_value_)
	);

	// forwarding
	assign sel_rs1_value_ = write_regf_en_r & (addr_rd_r == addr_rs1_);
	assign sel_rs2_value_ = write_regf_en_r & (addr_rd_r == addr_rs2_);
	assign rs1_value_ = sel_rs1_value_ ? rd_value_ : rs1_value;
	assign rs2_value_ = sel_rs2_value_ ? rd_value_ : rs2_value;
	
	// pipe 2 ID_EX
	logic [31:0] imm_r, rs1_value_r, rs2_value_r, alu_b_, alu_a_, flush_IDEX_r, base_addr_, j_addr_, mul_out, div_out;
	assign rst_or_flush_IDEX_r = rst | flush_IDEX_r;
	always_ff @(posedge clk) begin
		if (rst_or_flush_IDEX_r) begin
			write_regf_en_r <= 0;
			addr_rd_r <= 0;
			imm_r <= 0;
			rs1_value_r <= 0;
			rs2_value_r <= 0;
			op_r <= 0;
			sel_alu_b_r <= 0;
			pc_rr <= 0;
			flush_IDEX_r <= 0;
			flush_IFID_r <= 0;
			sel_pc_r <= 0;
			sel_jump_r <= 0;
			sel_alu_a_r <= 0;
			funct3_r <= 0;
			write_ram_r <= 0;
			sel_rd_value_r <= 0;
		end
		else begin
			write_regf_en_r <= write_regf_en_;
			addr_rd_r <= addr_rd_;
			imm_r <= imm_;
			rs1_value_r <= rs1_value_;
			rs2_value_r <= rs2_value_;
			op_r <= op_;
			sel_alu_b_r <= sel_alu_b_;
			pc_rr <= pc_r;
			flush_IDEX_r <= flush_IDEX_;
			flush_IFID_r <= flush_IFID_;
			sel_pc_r <= sel_pc_;
			sel_jump_r <= sel_jump_;
			sel_alu_a_r <= sel_alu_a_;
			funct3_r <= funct3_;
			write_ram_r <= write_ram_;
			sel_rd_value_r <= sel_rd_value_;
		end
	end
	
	// multi 2 to 1 (sel_alu_a_r)
	always_comb begin
		case (sel_alu_a_r)
			1'd0: alu_a_ = rs1_value_r;
			1'd1: alu_a_ = pc_rr;
		endcase
	end

	// multi 3 to 1 (sel_alu_b_r)
	always_comb begin
		unique case (sel_alu_b_r)
			2'd0: alu_b_ = imm_r;
			2'd1: alu_b_ = rs2_value_r;
			2'd2: alu_b_ = 4;
		endcase
	end
	
	// alu
	myalu alu_1 (
		.op (op_r),
		.alu_a (alu_a_),
		.alu_b (alu_b_),
		.alu_out (alu_out)
	);

	// mul
	MUL myMul (
		.funct3 (funct3_r),
		.rs1_value (rs1_value_r),
		.rs2_value (rs2_value_r),
		.mul_out (mul_out)
	);

	// div
	DIV myDiv (
		.funct3 (funct3_r),
		.rs1_value (rs1_value_r),
		.rs2_value (rs2_value_r),
		.div_out (div_out)
	);

	// LSU
	logic [31:0] read_data;
	mylsu lsu1 (
		.clk (clk),
		.write_ram (write_ram_r),
		.funct3 (funct3_r),
		.write_data (rs2_value_r),
		.ram_addr (alu_out),
		.read_data (read_data)
	);

	// multi 4 to 1
	always_comb begin
		case (sel_rd_value_r)
			2'd0: rd_value_ = alu_out;
			2'd1: rd_value_ = read_data;
			2'd2: rd_value_ = mul_out;
			2'd3: rd_value_ = div_out;
		endcase
	end

	// jump_addr_ (adder)
	// 2 to 1 multi (sel_jump_r)
	assign base_addr_ = sel_jump_r ? pc_rr : rs1_value_r;
	assign j_addr_ = base_addr_ + imm_r;
	assign jump_addr_ = {j_addr_[31:1], (j_addr_[0]&sel_jump_r)};
endmodule