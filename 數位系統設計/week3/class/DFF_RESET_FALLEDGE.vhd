library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DFF_RESET_FALLEDGE is
    port(
        CLK:in std_logic;
        D:in std_logic;
        Q:out std_logic;
        RESET:in std_logic
    );
end DFF_RESET_FALLEDGE;

architecture Behavioral of DFF_RESET_FALLEDGE is

begin
    process(CLK)
    begin
        if RESET = '1' then
            Q <= '0';
        elsif falling_edge(CLK) then
            Q <= D;
        end if;
    end process;
end Behavioral;