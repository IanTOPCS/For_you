module TOP (
    input logic rst, clk,
    output logic [7:0] w_q
);
    // other cnt
    logic cnt_pulse_1_;
    logic [1:0] cnt;
    always_ff @(posedge clk) begin
        if (rst) begin
            cnt <= 2'd0;
        end
        else if (cnt_pulse_1_) begin
            cnt <= cnt+1;
        end
    end

    // pc cnt
    logic load_pc;
    logic [3:0] pc_q, pc_next;
    always_ff @(posedge clk) begin
        if (rst) begin
            pc_q <= 4'd0;
        end
        else if (load_pc) begin
            pc_q <= pc_next;
        end
    end
    assign pc_next = pc_q + 4;

    // program_rom
    logic [31:0] rom_out;
    Program_Rom pr1 (
        .Rom_addr_in (pc_q),
        .Rom_data_out (rom_out)
    );

    logic load_data;
    logic [3:0] a_q, b_q, c_q, d_q, e_q, f_q, g_q, h_q;

    // DFF a
    always_ff @(posedge clk) begin
        if (rst) begin
            a_q <= 4'd0;
        end
        else if (load_data) begin
            a_q <= rom_out[3:0];
        end
    end

    // DFF b
    always_ff @(posedge clk) begin
        if (rst) begin
            b_q <= 4'd0;
        end
        else if (load_data) begin
            b_q <= rom_out[7:4];
        end
    end

    // DFF c
    always_ff @(posedge clk) begin
        if (rst) begin
            c_q <= 4'd0;
        end
        else if (load_data) begin
            c_q <= rom_out[11:8];
        end
    end

    // DFF d
    always_ff @(posedge clk) begin
        if (rst) begin
            d_q <= 4'd0;
        end
        else if (load_data) begin
            d_q <= rom_out[15:12];
        end
    end

    // DFF e
    always_ff @(posedge clk) begin
        if (rst) begin
            e_q <= 4'd0;
        end
        else if (load_data) begin
            e_q <= rom_out[19:16];
        end
    end

    // DFF f
    always_ff @(posedge clk) begin
        if (rst) begin
            f_q <= 4'd0;
        end
        else if (load_data) begin
            f_q <= rom_out[23:20];
        end
    end

    // DFF g
    always_ff @(posedge clk) begin
        if (rst) begin
            g_q <= 4'd0;
        end
        else if (load_data) begin
            g_q <= rom_out[27:24];
        end
    end

    // DFF h
    always_ff @(posedge clk) begin
        if (rst) begin
            h_q <= 4'd0;
        end
        else if (load_data) begin
            h_q <= rom_out[31:28];
        end
    end

    // mult sel_1
    logic [7:0] x, y, M;
    logic [1:0] sel_1, sel_2;
    always_comb begin
        case (sel_1)
            2'd0: x = {4'd0, a_q};
            2'd1: x = {4'd0, b_q};
            2'd2: x = {4'd0, c_q};
            2'd3: x = {4'd0, d_q};
        endcase
    end

    // mult sel_2
    always_comb begin
        case (sel_2)
            2'd0: y = {4'd0, e_q};
            2'd1: y = {4'd0, f_q};
            2'd2: y = {4'd0, g_q};
            2'd3: y = {4'd0, h_q};
        endcase
    end

    // M
    assign M = x * y;

    logic load_m0, load_m1, load_m2, load_m3, load_s, load_w;
    logic [7:0] M0_q, M1_q, M2_q, M3_q, S0, S1, S2, S3, S0_q, S1_q, S2_q, S3_q;

    // DFF M0
    always_ff @(posedge clk) begin
        if (rst) begin
            M0_q <= 8'd0;
        end
        else if (load_m0) begin
            M0_q <= M;
        end
    end

    // DFF M1
    always_ff @(posedge clk) begin
        if (rst) begin
            M1_q <= 8'd0;
        end
        else if (load_m1) begin
            M1_q <= M;
        end
    end

    // DFF M2
    always_ff @(posedge clk) begin
        if (rst) begin
            M2_q <= 8'd0;
        end
        else if (load_m2) begin
            M2_q <= M;
        end
    end

    // DFF M3
    always_ff @(posedge clk) begin
        if (rst) begin
            M3_q <= 8'd0;
        end
        else if (load_m3) begin
            M3_q <= M;
        end
    end

    // S0
    assign S0 = S0_q + M0_q;
    always_ff @(posedge clk) begin
        if (rst) begin
            S0_q <= 8'd0;
        end
        else if (load_s) begin
            S0_q <= S0;
        end
    end

    // S1
    assign S1 = S1_q + M1_q;
    always_ff @(posedge clk) begin
        if (rst) begin
            S1_q <= 8'd0;
        end
        else if (load_s) begin
            S1_q <= S1;
        end
    end

    // S2
    assign S2 = S2_q + M2_q;
    always_ff @(posedge clk) begin
        if (rst) begin
            S2_q <= 8'd0;
        end
        else if (load_s) begin
            S2_q <= S2;
        end
    end

    // S3
    assign S3 = S3_q + M3_q;
    always_ff @(posedge clk) begin
        if (rst) begin
            S3_q <= 8'd0;
        end
        else if (load_s) begin
            S3_q <= S3;
        end
    end

    // DFF W
    always_ff @(posedge clk) begin
        if (rst) begin
            w_q <= 8'd0;
        end
        else if (load_w) begin
            w_q <= ((S0_q - S1_q) + (S2_q - S3_q));
        end
    end

    // controller
    typedef enum logic [2:0] { t0=3'd0, t1=3'd1, t2=3'd2, t3=3'd3, t4=3'd4, t5=3'd5, t6=3'd6, t7=3'd7 } state_t;
    state_t ps, ns;

    // initial state
    always_ff @(posedge clk) begin
        if (rst) begin
            ps <= t0;
        end
        else begin
            ps <= ns;
        end
    end

    always_comb begin
        cnt_pulse_1_ = 0;
        load_pc = 0;
        load_data = 0;
        sel_1 = 2'd0;
        sel_2 = 2'd0;
        load_m0 = 0;
        load_m1 = 0;
        load_m2 = 0;
        load_m3 = 0;
        load_s = 0;
        load_w = 0;
        ns = ps;
        case (ps)
            t0: begin
                ns = t1;
            end
            t1: begin
                load_data = 1;
                load_pc = 1;
                ns = t2;
            end
            t2: begin
                sel_1 = 2'd0;
                sel_2 = 2'd2;
                load_m0 = 1;
                ns = t3;
            end
            t3: begin
                sel_1 = 2'd1;
                sel_2 = 2'd3;
                load_m1 = 1;
                ns = t4;
            end
            t4: begin
                sel_1 = 2'd2;
                sel_2 = 2'd0;
                load_m2 = 1;
                ns = t5;
            end
            t5: begin
                sel_1 = 2'd3;
                sel_2 = 2'd1;
                load_m3 = 1;
                ns = t6;
            end
            t6: begin
                load_s = 1;
                if (cnt < 3) begin
                    cnt_pulse_1_ = 1;
                    ns = t1;
                end
                else begin
                    ns = t7;
                end
            end
            t7: begin
                load_w = 1;
                ns = t7;
            end
        endcase
    end
endmodule