module Program_Rom(
   output logic [31:0] Rom_data,
   input [31:0] Rom_addr
);

   always_comb begin
      case (Rom_addr)
         32'h00000000 : Rom_data = 32'h00100093; // addi x1 x0 1
         32'h00000004 : Rom_data = 32'h00A02113; // slti x2 x0 10
         32'h00000008 : Rom_data = 32'h00F03193; // sltiu x3 x0 15
         32'h0000000C : Rom_data = 32'h00F0C213; // xori x4 x1 15
         32'h00000010 : Rom_data = 32'h00716293; // ori x5 x2 7
         32'h00000014 : Rom_data = 32'h0031F313; // andi x6 x3 3
         32'h00000018 : Rom_data = 32'h00221393; // slli x7 x4 2
         32'h0000001C : Rom_data = 32'h0012D413; // srli x8 x5 1
         32'h00000020 : Rom_data = 32'h40125493; // srai x9 x4 1
         32'h00000024 : Rom_data = 32'h00208633; // add x12 x1 x2
         32'h00000028 : Rom_data = 32'h404186B3; // sub x13 x3 x4
         32'h0000002C : Rom_data = 32'h00B52733; // slt x14 x10 x11
         32'h00000030 : Rom_data = 32'h007437B3; // sltu x15 x8 x7
         32'h00000034 : Rom_data = 32'h0045F833; // and x16 x11 x4
         32'h00000038 : Rom_data = 32'h00C5E8B3; // or x17 x11 x12
         32'h0000003C : Rom_data = 32'h00E6C933; // xor x18 x13 x14
         32'h00000040 : Rom_data = 32'h001799B3; // sll x19 x15 x1
         32'h00000044 : Rom_data = 32'h00285A33; // srl x20 x16 x2
         32'h00000048 : Rom_data = 32'h4038DAB3; // sra x21 x17 x3
         32'h0000004C : Rom_data = 32'h00208463; // beq x1 x2 8
         32'h00000050 : Rom_data = 32'h00000B13; // addi x22 x0 0
         32'h00000054 : Rom_data = 32'h00100B13; // addi x22 x0 1
         32'h00000058 : Rom_data = 32'h00419463; // bne x3 x4 8
         32'h0000005C : Rom_data = 32'h00000B93; // addi x23 x0 0
         32'h00000060 : Rom_data = 32'h00100B93; // addi x23 x0 1
         32'h00000064 : Rom_data = 32'h0062C463; // blt x5 x6 8
         32'h00000068 : Rom_data = 32'h00000C13; // addi x24 x0 0
         32'h0000006C : Rom_data = 32'h00100C13; // addi x24 x0 1
         32'h00000070 : Rom_data = 32'h0083D463; // bge x7 x8 8
         32'h00000074 : Rom_data = 32'h00000C93; // addi x25 x0 0
         32'h00000078 : Rom_data = 32'h00100C93; // addi x25 x0 1
         32'h0000007C : Rom_data = 32'h00A4E463; // bltu x9 x10 8
         32'h00000080 : Rom_data = 32'h00000D13; // addi x26 x0 0
         32'h00000084 : Rom_data = 32'h00100D13; // addi x26 x0 1
         32'h00000088 : Rom_data = 32'h00C5F463; // bgeu x11 x12 8
         32'h0000008C : Rom_data = 32'h00000D93; // addi x27 x0 0
         32'h00000090 : Rom_data = 32'h00100D93; // addi x27 x0 1
         32'h00000094 : Rom_data = 32'h01400E6F; // jal x28 20
         32'h00000098 : Rom_data = 32'h00730EB3; // add x29 x6 x7
         32'h0000009C : Rom_data = 32'h12345537; // lui x10 74565
         32'h000000A0 : Rom_data = 32'h20000597; // auipc x11 131072
         32'h000000A4 : Rom_data = 32'h00C0006F; // jal x0 12
         32'h000000A8 : Rom_data = 32'h00100213; // addi x4 x0 1
         32'h000000AC : Rom_data = 32'h000E0267; // jalr x4 x28 0
         32'h000000B0 : Rom_data = 32'h00000013; // addi x0 x0 0
         default : Rom_data = 32'h00000013;      // NOP
      endcase
   end

endmodule
