`timescale 1ns/100ps
module testbench;
  logic rst;
  logic clk;
  
  mycpu cpu(
	  .rst      (rst      ),
	  .clk      (clk      )
  );
  
  initial
  begin
    clk = 0;
    rst = 1;
    #20 rst = 0;
    #5000 $stop;
  end
  
  always #5 clk = ~clk;
endmodule