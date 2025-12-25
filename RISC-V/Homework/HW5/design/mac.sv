module mac(
    input logic rst, clk,
    output logic [7:0] port_A, port_B
);
    logic [3:0] cnt1, cnt2;
    logic [7:0] M, S, W;
    logic load_w, load_a, load_b;
    typedef enum logic { start = 1'd0, load = 1'd1 } state_t;
    state_t ps, ns;
    // counter 1, 2
    always_ff @(posedge clk) begin
        if (rst) begin
            cnt1 <= 4'd0;
            cnt2 <= 4'd0;
        end
        else begin
            cnt1 <= cnt1 + 1;
            cnt2 <= cnt2 + 1;
        end
    end

    // multiple cnt1, cnt2 every time
    assign M = cnt1 * cnt2;

    // s = w + m
    assign S = W + M;

    // W flip-flop
    always_ff @(posedge clk) begin
        if (rst) begin
            W <= 8'd0;
        end
        else begin
            if (load_w) begin
                W <= S;
            end
        end
    end

    // port_A flip-flop
    always_ff @(posedge clk) begin
        if (rst) begin
            port_A <= 8'd0;
        end
        else begin
            if (load_a) begin
                port_A <= W;
            end
        end
    end

    // port_B flip-flop
    always_ff @(posedge clk) begin
        if (rst) begin
            port_B <= 8'd0;
        end
        else begin
            if (load_b) begin
                port_B <= W;
            end
        end
    end

    // initial FSM state to "start"
    always_ff @(posedge clk) begin
        if (rst) begin
            ps <= start;
        end
        else begin
            ps <= ns;
        end
    end

    // FSM controller
    always_comb begin
        load_w = 0;
        load_a = 0;
        load_b = 0;
        ns = ps;
        case (ps)
            start: begin
                ns = load;
            end
            load: begin
                if (S >= 8'd10) begin
                    load_w = 1;
                end
                if (W < 8'd63) begin
                    load_a = 1;
                end
                else if (W >= 8'd63) begin
                    load_b = 1;
                end
                ns = load;
            end
        endcase
    end
endmodule