`define I_NOP 32'h13
module mycpu(
	input logic clk, rst
);
	
	logic rst_pc_;
	logic [31:0] pc,pc_next, pc_r;
	assign pc_next = pc+4;
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
	logic flush_IFID_;
	logic [31:0] inst_r;
	assign rst_or_flush_IFID_ = rst | flush_IFID_;
	always_ff @(posedge clk) begin
		if (rst_or_flush_IFID_) begin
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
	logic [2:0] funct3_;
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
	logic write_regf_en_r;
	logic [4:0] addr_rd_r;
	logic [31:0] rd_value, rs1_value, rs2_value;
	Reg_file myreg (
		.clk (clk),
		.rst (rst),
		.write_regf_en (write_regf_en_r),
		.addr_rd (addr_rd_r),
		.addr_rs1 (addr_rs1_),
		.addr_rs2 (addr_rs2_),
		.rd_value (rd_value),
		.rs1_value (rs1_value),
		.rs2_value (rs2_value)
	);
	
	// pipe 2 ID_EX
	logic flush_IDEX_;
	assign rst_or_flush_IDEX_ = rst | flush_IDEX_;
	logic [31:0] imm_r, rs1_value_r, rs2_value_r;
	always_ff @(posedge clk) begin
		if (rst_or_flush_IDEX_) begin
			write_regf_en_r <= 0;
			addr_rd_r <= 0;
			imm_r <= 0;
			rs1_value_r <= 0;
			rs2_value_r <= 0;
		end
	end
	
	// controller
	logic sel_pc;
	controller mycontroller(
		// in
		.funct7_ (funct7_),
		.opcode_ (opcode_),
		.rst (rst),
		.clk (clk),
		.funct3_ (funct3_),
		// out
		.flush_IFID_ (flush_IFID_),
		.flush_IDEX_ (flush_IDEX_),
		.rst_pc_ (rst_pc_),
		.sel_pc (sel_pc)
	);
endmodule