module testbench;
    logic clk, rst;
    logic [7:0] W_q;

    top top1(
        .clk (clk),
        .rst (rst),
        .W_q (W_q)
    );

    always #5 clk = ~clk;

    initial begin
            clk = 0; rst = 1;
        #10 rst = 0;
        #500 $stop;
    end
endmodule