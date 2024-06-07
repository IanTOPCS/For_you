library verilog;
use verilog.vl_types.all;
entity accumulator_top is
    port(
        \out\           : out    vl_logic_vector(3 downto 0);
        clk             : in     vl_logic;
        reset           : in     vl_logic
    );
end accumulator_top;
