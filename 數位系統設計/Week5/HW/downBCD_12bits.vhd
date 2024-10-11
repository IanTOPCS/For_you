library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity downBCD_12bits is
    port(
        casin:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(11 downto 0)
    );
end entity;

architecture downBCD_12bits of downBCD_12bits is
    signal casout1, casout2:std_logic;
    signal cnt:std_logic_vector(11 downto 0);
    component downBCD_4bits is
        port(
        casin:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
    end component;
begin
    downBCD1:downBCD_4bits port map(casin, clk, reset, casout1, Q(3 downto 0));
    downBCD2:downBCD_4bits port map(casout1, clk, reset, casout2, Q(7 downto 4));
    downBCD3:downBCD_4bits port map(casout2, clk, reset, casout, Q(11 downto 8));
end downBCD_12bits;