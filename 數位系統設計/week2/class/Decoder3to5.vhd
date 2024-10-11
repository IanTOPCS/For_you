library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Decorder3to5 is
    port(
        A, B, C:in std_logic:='0';
        Y:out std_logic_vector(4 downto 0):="00000"
    );
end Decorder3to5;

architecture Decorder3to5 of Decorder3to5 is
    signal ABC:std_logic_vector(2 downto 0);
begin
    ABC <= A & B & C;
    Y <= "11110" when (ABC = "000" or ABC = "001") else
         "11101" when ABC = "010" else
         "11011" when (ABC = "011" or ABC = "100" or ABC = "101") else
         "10111" when ABC = "110" else
         "01111" when ABC = "111";
end Decorder3to5;