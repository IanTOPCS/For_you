library verilog;
use verilog.vl_types.all;
entity DFF_pos is
    port(
        data            : in     vl_logic;
        reset           : in     vl_logic;
        clk             : in     vl_logic;
        q               : out    vl_logic
    );
end DFF_pos;
