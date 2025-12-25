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
    #40 rst = 0;
    #3000 $stop;
  end
  
  always #10 clk = ~clk;
endmodule