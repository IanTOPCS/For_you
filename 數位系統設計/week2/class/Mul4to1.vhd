library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Mul4to1 is
    port(
        I:in std_logic_vector(3 downto 0);
        S:in std_logic_vector(1 downto 0);
        Y:out std_logic
    );
end Mul4to1;

architecture Mul4to1 of Mul4to1 is

begin
    Y <= I(0) when S = "00" else
         I(1) when S = "01" else
         I(2) when S = "10" else
         I(3) when S = "11";
end Mul4to1;