module simplePipe (
    input logic rst, clk,
    input logic [3:0] A, B, C, D, E,
    output logic [3:0] y
);
    // pipe 1
    logic [3:0] sum_, sum_r, sub_, sub_r, e_, e_r;
    assign sum_ = A+B;
    assign sub_ = C-D;
    assign e_ = E;
    always_ff @(posedge clk) begin
        if (rst) begin
            sum_r <= 0;
            sub_r <= 0;
            e_r <= 0;
        end
        else begin
            sum_r <= sum_;
            sub_r <= sub_;
            e_r <= e_;
        end
    end

    // pipe 2
    logic [3:0] afterAnd_, afterAnd_r, e_rr;
    assign afterAnd_ = sum_r & sub_r;
    always_ff @(posedge clk) begin
        if (rst) begin
            e_rr <= 0;
            afterAnd_r <= 0;
        end
        else begin
            e_rr <= e_r;
            afterAnd_r <= afterAnd_;
        end
    end

    // after pipe2 'or'
    assign y = afterAnd_r | e_rr;
endmodule