library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Mux4to1_en is
    port(
        I:in std_logic_vector(3 downto 0);
        S:in std_logic_vector(1 downto 0);
        en:in std_logic;
        Y:out std_logic
    );
end Mux4to1_en;

architecture Mux4to1_en of Mux4to1_en is

begin
    Y <= '0' when en = '1' else
         I(0) when S = "00" else
         I(1) when S = "01" else
         I(2) when S = "10" else
         I(3) when S = "11";
end Mux4to1_en;