module testbench;
  logic [1:0] R, Y, G;
  logic clk;
  logic rst;
  
  traffic_light u_traffic_light (
	  .R   (R   ),
	  .Y   (Y   ),
	  .G   (G   ),
	  .clk (clk ),
	  .rst (rst )
  );
  
  initial begin
    clk = 0; rst = 1;
    #15 rst = 0;
    #3000 $stop;
  end
  
  always #10 clk = ~clk;
	
endmodule