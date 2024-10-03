library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DEMUL1to2 is
    port(
        DIN:in std_logic;
        S:in std_logic;
        Y:out std_logic_vector(1 downto 0)
    );
end DEMUL1to2;

architecture behavior of DEMUL1to2 is
begin
    process(S, DIN)
    begin
        if S = '0' then
            Y <= '1' & DIN;
        elsif S = '1' then
            Y <= DIN & '1';
        end if;
    end process;
end behavior ; -- behavior