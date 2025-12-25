module Program_Rom (
    input [3:0] Rom_addr_in,
    output logic [15:0] Rom_data_out
);
    always_comb begin
        case (Rom_addr_in)
            4'h0: Rom_data_out = 16'h1234;
            4'h1: Rom_data_out = 16'h2138;
            4'h2: Rom_data_out = 16'h1256;
            4'h3: Rom_data_out = 16'h7757;
            default: Rom_data_out = 16'h0;
        endcase
    end
endmodule