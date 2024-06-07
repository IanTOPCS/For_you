library verilog;
use verilog.vl_types.all;
entity adder4 is
    port(
        A               : in     vl_logic_vector(3 downto 0);
        B               : in     vl_logic_vector(3 downto 0);
        S               : out    vl_logic_vector(3 downto 0);
        cout            : out    vl_logic;
        cin             : in     vl_logic
    );
end adder4;
