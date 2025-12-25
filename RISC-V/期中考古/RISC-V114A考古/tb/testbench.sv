module testbench;
  logic clk, rst;
  logic [7:0] w_q;

  TOP u_TOP (
    .rst (rst),
    .clk (clk),
    .w_q (w_q)
  );

  always #10 clk = ~clk;
  initial begin
    clk = 0; rst = 1;
    #15 rst = 0;
    #10000 $stop;
  end
endmodule