`timescale 1ns/100ps
module clock_divider(
    input logic clk,
    input logic rst,
	input logic [31:0] DIVISOR,
	//
    output logic clk_out
);

    logic [32:0] counter;

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            counter <= 0;
            clk_out <= 0;
        end else begin
            if (counter == (DIVISOR - 1)) begin
                counter <= 0;
                clk_out <= ~clk_out;
            end else begin
                counter <= counter + 1;
            end
        end
    end

endmodule
