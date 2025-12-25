module Program_Rom(
   output logic [31:0] Rom_data,
   input [31:0] Rom_addr
);

   always_comb begin
      case (Rom_addr)
         32'h00000000 : Rom_data = 32'h00020137; // init:   lui      x2, 32
         32'h00000004 : Rom_data = 32'h00110113; //         addi     x2, x2, 1
         32'h00000008 : Rom_data = 32'h00202023; //         sw       x2, 0(x1)
         32'h0000000C : Rom_data = 32'h00040137; //         lui      x2, 64
         32'h00000010 : Rom_data = 32'h00310113; //         addi     x2, x2, 3
         32'h00000014 : Rom_data = 32'h00202223; //         sw       x2, 4(x0)
         32'h00000018 : Rom_data = 32'h00060137; //         lui      x2, 96
         32'h0000001C : Rom_data = 32'h00510113; //         addi     x2, x2, 5
         32'h00000020 : Rom_data = 32'h00202423; //         sw       8(x0)
         32'h00000024 : Rom_data = 32'h00200113; //         li       x2, 2
         32'h00000028 : Rom_data = 32'h00000193; //         addi     x3, x0, 0
         32'h0000002C : Rom_data = 32'h0001a203; // loop:   lw       x4, 0(x3)
         32'h00000030 : Rom_data = 32'h000202db; //         xch16.r  x5, x4
         32'h00000034 : Rom_data = 32'h00418193; //         addi     x3, x3, 4
         32'h00000038 : Rom_data = 32'he801217b; //         cnzdecj  x2, x2, loop
         default : Rom_data = 32'h00000013;      // NOP
      endcase
   end

endmodule
