library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Mux16to1 is
    port(
        S:in std_logic_vector(3 downto 0);
        I:in std_logic_vector(15 downto 0);
        Y:out std_logic
    );
end Mux16to1;

architecture Mux16to1 of Mux16to1 is
    signal II:std_logic_vector(3 downto 0);
begin
    II(0) <= I(0) when S(1 downto 0) = "00" else
             I(1) when S(1 downto 0) = "01" else
             I(2) when S(1 downto 0) = "10" else
             I(3) when S(1 downto 0) = "11";

    II(1) <= I(4) when S(1 downto 0) = "00" else
             I(5) when S(1 downto 0) = "01" else
             I(6) when S(1 downto 0) = "10" else
             I(7) when S(1 downto 0) = "11";
    
    II(2) <= I(8) when S(1 downto 0) = "00" else
             I(9) when S(1 downto 0) = "01" else
             I(10) when S(1 downto 0) = "10" else
             I(11) when S(1 downto 0) = "11";
    
    II(3) <= I(12) when S(1 downto 0) = "00" else
             I(13) when S(1 downto 0) = "01" else
             I(14) when S(1 downto 0) = "10" else
             I(15) when S(1 downto 0) = "11";

    Y <= II(0) when S(3 downto 2) = "00" else
         II(1) when S(3 downto 2) = "01" else
         II(2) when S(3 downto 2) = "10" else
         II(3) when S(3 downto 2) = "11";
end Mux16to1;