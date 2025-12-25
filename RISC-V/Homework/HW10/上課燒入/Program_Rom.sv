`timescale 1ns/100ps
module Program_Rom(
	input	logic [31:0] Rom_addr,
	output	logic [31:0] Rom_data
);    
  
    always_comb begin
        case (Rom_addr)
			32'h0  : Rom_data = 32'h00000f93;	//init:			li x31, 0 
			32'h4  : Rom_data = 32'h001f8f93;   //loop:			addi x31, x31, 1
			32'h8  : Rom_data = 32'h00000317;   //				auipc x6 0
			32'hc  : Rom_data = 32'h00c300e7;   //				jalr x1 x6 12
			32'h10 : Rom_data = 32'hff5ff06f;   //				j loop
			32'h14 : Rom_data = 32'h00001537;   //delay:		lui x10 1
			32'h18 : Rom_data = 32'h38850513;   //				addi x10 x10 904
			32'h1c : Rom_data = 32'h000025b7;   //outer_loop:	lui x11 2
			32'h20 : Rom_data = 32'h71058593;   //				addi x11 x11 1808
			32'h24 : Rom_data = 32'h00000013;   //				nop
			32'h28 : Rom_data = 32'h00000013;   //				nop
			32'h2c : Rom_data = 32'hfff58593;   //inner_loop:	addi x11, x11, -1 
			32'h30 : Rom_data = 32'h00000013;   //				nop
			32'h34 : Rom_data = 32'h00000013;   //				nop
			32'h38 : Rom_data = 32'hfe059ae3;   //				bnez x11, inner_loop
			32'h3C : Rom_data = 32'hfff50513;   //				addi x10, x10, -1
			32'h40 : Rom_data = 32'h00000013;   //				nop
			32'h44 : Rom_data = 32'h00000013;   //				nop
			32'h48 : Rom_data = 32'hfc051ae3;   //				bnez x10, outer_loop
			32'h4C : Rom_data = 32'h00008067;   //				ret
            default: Rom_data = 32'h00000013;   //NOP
        endcase
    end
endmodule

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





































































































































































