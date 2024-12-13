library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity upBCD_16bits is
    port(
        clk:in std_logic;
        reset:in std_logic;
        stop_pos:in std_logic;
        casout:out std_logic;
        -- look:out std_logic_vector(0 to 2);  -- 觀察進位的flag
        Q:out std_logic_vector(15 downto 0)
    );
end entity;

architecture upBCD_16bits of upBCD_16bits is
    component upBCD_4bits is
    port(
        clk:in std_logic;
        reset:in std_logic;
        stop_pos:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
    end component;
    signal casout_in:std_logic_vector(0 to 2):=(others => '0');
begin
    upBCD0:upBCD_4bits port map(clk, reset, stop_pos, casout_in(0), Q(3 downto 0));
    upBCD1:upBCD_4bits port map(casout_in(0), reset, stop_pos, casout_in(1), Q(7 downto 4));
    upBCD2:upBCD_4bits port map(casout_in(1), reset, stop_pos, casout_in(2), Q(11 downto 8));
    upBCD3:upBCD_4bits port map(casout_in(2), reset, stop_pos, casout, Q(15 downto 12));

    -- look <= casout_in;
end upBCD_16bits;