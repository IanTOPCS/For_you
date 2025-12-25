module mux (
    input logic [2:0] a [0:7],
    input logic [2:0] sel,
    output logic [2:0] y
);
    always_comb begin
        case (sel)
            3'd0: y = a[0];
            3'd1: y = a[1];
            3'd2: y = a[2];
            3'd3: y = a[3];
            3'd4: y = a[4];
            3'd5: y = a[5];
            3'd6: y = a[6];
            3'd7: y = a[7];
        endcase
    end
endmodule