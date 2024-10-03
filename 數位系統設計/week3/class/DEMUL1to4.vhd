library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DEMUL1to4 is
    port(
        DIN:in std_logic;
        S:in std_logic_vector(1 downto 0);
        Y:out std_logic_vector(3 downto 0)
    );
end DEMUL1to4;

architecture DEMUL1to4 of DEMUL1to4 is

begin
    process(S, DIN)
    begin
        case S is
            when "00" => Y <= "111" & DIN;
            when "01" => Y <= "11" & DIN & '1';
            when "10" => Y <= '1' & DIN & "11";
            when others => Y <= DIN & "111";
        end case;
    end process;
end DEMUL1to4;