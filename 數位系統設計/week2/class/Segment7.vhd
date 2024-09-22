library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Segment7 is
    port(
        BCD:in std_logic_vector(3 downto 0);
        segment:out std_logic_vector(6 downto 0)
    );
end Segment7;

architecture Segment7 of Segment7 is

begin
    segment <= "1000000" when BCD = x"0" else
               "1111001" when BCD = x"1" else
               "0100100" when BCD = x"2" else
               "0110000" when BCD = x"3" else
               "0011001" when BCD = x"4" else
               "0010010" when BCD = x"5" else
               "0000010" when BCD = x"6" else
               "1111000" when BCD = x"7" else
               "0000000" when BCD = x"8" else
               "0010000" when BCD = x"9" else
               "0001000" when BCD = x"A" else
               "0000011" when BCD = x"B" else
               "0100111" when BCD = x"C" else
               "0100001" when BCD = x"D" else
               "0000110" when BCD = x"E" else
               "0001110" when BCD = x"F";
end Segment7;