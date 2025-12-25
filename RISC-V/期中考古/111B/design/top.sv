module top(
    input logic rst, clk,
    output logic [7:0] W_q
);
    // other counter
    logic [7:0] cnt;
    always_ff @(posedge clk) begin
        if (rst) begin
            cnt <= 8'd0;
        end
        else begin
            cnt <= cnt+1;
        end
    end

    // clock counter
    logic [3:0] pc_q, pc_next;
    logic reset_pc, load_pc;
    always_ff @(posedge clk) begin
        if (rst|reset_pc) begin
            pc_q <= 4'd0;
        end
        else if (load_pc) begin
            pc_q <= pc_next;
        end
    end
    assign pc_next = pc_q+1;

    // program_rom
    logic [15:0] Rom_out;
    Program_Rom pr1 (
        // input
        .Rom_addr_in (pc_q),
        // output
        .Rom_data_out (Rom_out)
    );

    // circuit
    logic load_reg, sel_mult1, load_W;
    logic [1:0] sel_mult;
    logic [3:0] a_q, b_q, c_q, d_q;
    logic [7:0] x, y, s;
    // DFF a
    always_ff @(posedge clk) begin
        if (rst) begin
            a_q <= 4'd0;
        end
        else if (load_reg) begin
            a_q <= Rom_out[3:0];
        end
    end

    // DFF b
    always_ff @(posedge clk) begin
        if (rst) begin
            b_q <= 4'd0;
        end
        else if (load_reg) begin
            b_q <= Rom_out[7:4];
        end
    end

    // DFF c
    always_ff @(posedge clk) begin
        if (rst) begin
            c_q <= 4'd0;
        end
        else if (load_reg) begin
            c_q <= Rom_out[11:8];
        end
    end

    // DFF d
    always_ff @(posedge clk) begin
        if (rst) begin
            d_q <= 4'd0;
        end
        else if (load_reg) begin
            d_q <= Rom_out[15:12];
        end
    end

    // multi1
    always_comb begin
        case (sel_mult1)
            1'd0: x = W_q;
            1'd1: x = {4'h0, a_q};
        endcase
    end

    // mult
    always_comb begin
        case (sel_mult)
            2'd0: y = {4'h0, b_q};
            2'd1: y = {4'h0, c_q};
            2'd2: y = {4'h0, d_q};
        endcase
    end

    // ALU (0:+, 1:-, 2:*)
    logic [1:0] op;
    always_comb begin
        case (op)
            2'd0: s = x+y;
            2'd1: s = x-y;
            2'd2: s = x*y;
        endcase
    end

    // DFF w
    always_ff @(posedge clk) begin
        if (rst) begin
            W_q <= 8'd0;
        end
        else if (load_W) begin
            W_q <= s;
        end
    end


    // controller
    typedef enum logic[2:0] { t1=3'd1, t2=3'd2, t3=3'd3, t4=3'd4 } state_t;
    state_t ps, ns;

    // initail state
    always_ff @(posedge clk) begin
        if (rst) begin
            ps <= t1;
        end
        else begin
            ps <= ns;
        end
    end

    always_comb begin
        reset_pc = 0;
        load_pc = 0;
        load_reg = 0;
        sel_mult1 = 2'd0;
        sel_mult = 0;
        op = 0;
        load_W = 0;
        ns = ps;
        case (ps)
            t1: begin
                load_pc = 1;
                load_reg = 1;
                ns = t2;
            end
            t2: begin
                sel_mult1 = 1;
                sel_mult = 2'd2;
                op = 2'd0;
                load_W = 1;
                ns = t3;
            end
            t3: begin
                sel_mult = 2'd0;
                op = 2'd2;
                load_W = 1;
                ns = t4;
            end
            t4: begin
                sel_mult = 3'd1;
                op = 2'd1;
                load_W = 1;
                load_pc = 1;
                load_reg = 1;
                ns = t2;
            end
        endcase
    end
endmodule