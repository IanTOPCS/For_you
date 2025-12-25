module Program_Rom (
    input logic [3:0] Rom_addr_in,
    output logic [31:0] Rom_data_out
);
    always_comb begin
        case (Rom_addr_in)
            4'h0: Rom_data_out = 32'h44216a93;
            4'h4: Rom_data_out = 32'h65125748;
            4'h8: Rom_data_out = 32'hffb00193;
            4'hc: Rom_data_out = 32'h156778dc;
            default: Rom_data_out = 32'h0;
        endcase
    end
endmodule