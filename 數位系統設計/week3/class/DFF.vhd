library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DFF_CNT is
    port(
        CLK:in std_logic;
        D:in std_logic;
        Q:out std_logic;
        RESET:in std_logic
    );
end DFF_CNT;

architecture Behavioral of DFF_CNT is

begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            Q <= D;
        end if;
    end process;
end Behavioral;