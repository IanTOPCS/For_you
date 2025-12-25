module Program_Rom(
   output logic [31:0] Rom_data,
   input [31:0] Rom_addr
);

   always_comb begin
      case (Rom_addr)
         32'h00000000 : Rom_data = 32'h00500113; // addi x2 x0 5
         32'h00000004 : Rom_data = 32'h0FBD01B7; // lui x3 64464
         32'h00000008 : Rom_data = 32'h06318193; // addi x3 x3 99
         32'h0000000C : Rom_data = 32'h00312023; // sw x3 0(x2)
         32'h00000010 : Rom_data = 32'h6E0561B7; // lui x3 450646
         32'h00000014 : Rom_data = 32'hFF518193; // addi x3 x3 -11
         32'h00000018 : Rom_data = 32'h00312223; // sw x3 4(x2)
         32'h0000001C : Rom_data = 32'h000051B7; // lui x3 5
         32'h00000020 : Rom_data = 32'hDF718193; // addi x3 x3 -521
         32'h00000024 : Rom_data = 32'h00312423; // sw x3 8(x2)
         32'h00000028 : Rom_data = 32'h00000317; // auipc x6 0
         32'h0000002C : Rom_data = 32'h00C300E7; // jalr x1 x6 12
         32'h00000030 : Rom_data = 32'h00000013; // addi x0 x0 0
         32'h00000034 : Rom_data = 32'h00010183; // lb x3 0(x2)
         32'h00000038 : Rom_data = 32'h00110113; // addi x2 x2 1
         32'h0000003C : Rom_data = 32'h00E00293; // addi x5 x0 14
         32'h00000040 : Rom_data = 32'h00010203; // lb x4 0(x2)
         32'h00000044 : Rom_data = 32'h0041CC63; // blt x3 x4 24
         32'h00000048 : Rom_data = 32'h00110113; // addi x2 x2 1
         32'h0000004C : Rom_data = 32'hFE511AE3; // bne x2 x5 -12
         32'h00000050 : Rom_data = 32'h00100313; // addi x6 x0 1
         32'h00000054 : Rom_data = 32'h02618FB3; // mul x31 x3 x6
         32'h00000058 : Rom_data = 32'h00008067; // jalr x0 x1 0
         32'h0000005C : Rom_data = 32'h00010183; // lb x3 0(x2)
         32'h00000060 : Rom_data = 32'hFE9FF06F; // jal x0 -24
         default : Rom_data = 32'h00000013;      // NOP
      endcase
   end

endmodule
