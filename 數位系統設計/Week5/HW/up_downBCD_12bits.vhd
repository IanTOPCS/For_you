library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity up_downBCD_12bits is
    port(
        casin:in std_logic;
        up_down:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(11 downto 0)
    );
end up_downBCD_12bits;

architecture up_downBCD_12bits of up_downBCD_12bits is
    signal casout1, casout2:std_logic;
    component up_downBCD_4bits is
        port(
        casin:in std_logic;
        up_down:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
    end component;
begin
    up_downBCD1:up_downBCD_4bits port map(casin, up_down, clk, reset, casout1, Q(3 downto 0));
    up_downBCD2:up_downBCD_4bits port map(casout1, up_down, clk, reset, casout2, Q(7 downto 4));
    up_downBCD3:up_downBCD_4bits port map(casout2, up_down, clk, reset, casout, Q(11 downto 8));
end up_downBCD_12bits;