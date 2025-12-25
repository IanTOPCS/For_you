module alu (
    input logic [7:0] A, B,
    input logic [2:0] op,
    output logic [7:0] S
);
    always_comb begin
        unique case (op)
            3'd0: S = A + B;
            3'd1: S = A - B;
        endcase
    end
endmodule