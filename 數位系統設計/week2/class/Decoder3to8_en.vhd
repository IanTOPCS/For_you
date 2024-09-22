library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Decoder3to8_en is
    port(
        A:in std_logic_vector(2 downto 0);
        Y:out std_logic_vector(7 downto 0);
        en:in std_logic
    );
end Decoder3to8_en;

architecture Decoder3to8_en of Decoder3to8_en is

begin
    Y <= "00000000" when en = '1' else
         "00000001" when A = "000" else
         "00000010" when A = "001" else
         "00000100" when A = "010" else
         "00001000" when A = "011" else
         "00010000" when A = "100" else
         "00100000" when A = "101" else
         "01000000" when A = "110" else
         "10000000" when A = "111";
end Decoder3to8_en;