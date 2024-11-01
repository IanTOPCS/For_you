library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity decorder_7seg is
    port(
        BCD:in std_logic_vector(3 downto 0);
        HEX:out std_logic_vector(6 downto 0)
    );
end decorder_7seg;

architecture decorder_7seg of decorder_7seg is
begin
    HEX <= "1000000" when BCD = "0000" else
           "1111001" when BCD = "0001" else
           "0100100" when BCD = "0010" else
           "0110000" when BCD = "0011" else
           "0011001" when BCD = "0100" else
           "0010010" when BCD = "0101" else
           "0000010" when BCD = "0110" else
           "1111000" when BCD = "0111" else
           "0000000" when BCD = "1000" else
           "0010000" when BCD = "1001" else
           "1111111";
end decorder_7seg;