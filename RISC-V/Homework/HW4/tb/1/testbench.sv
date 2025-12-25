module testbench;
  logic [3:0] y;
  logic rst;
  logic clk;
  
  relu u_relu(
	  .y      	(y    	  ),
	  .rst      (rst      ),
	  .clk      (clk      )
  );
  
  initial
  begin
    clk = 0;
    rst = 1;
    #20 rst = 0;
    #3000 $stop;
  end
  
  always #10 clk = ~clk;
endmodule