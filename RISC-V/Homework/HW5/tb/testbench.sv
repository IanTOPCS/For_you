module testbench;
  logic [7:0] port_A;
  logic [7:0] port_B;
  logic rst;
  logic clk;
  
  mac u_mac(
	  .port_A   (port_A	  ),
	  .port_B   (port_B	  ),
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