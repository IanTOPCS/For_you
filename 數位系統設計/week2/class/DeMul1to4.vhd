library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DeMul1to4 is
    port(
        DIN:in std_logic;
        S:in std_logic_vector(1 downto 0);
        Y:out std_logic_vector(3 downto 0)
    );
end DeMul1to4;

architecture DeMul1to4 of DeMul1to4 is

begin
    Y <= "111" & DIN when S = "00" else
         "11" & DIN & '1' when S = "01" else
         '1' & DIN & "11" when S = "10" else
         DIN & "111";
end DeMul1to4;