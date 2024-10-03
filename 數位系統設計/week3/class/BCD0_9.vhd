library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity BCD0_9 is
    port(
        RESET:in std_logic;
        CLK:in std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end BCD0_9;

architecture BCD0_9 of BCD0_9 is
    signal tmp:std_logic_vector(3 downto 0);
begin
    process(CLK, RESET)
    begin
        if RESET='0' then
            tmp <= (others => '0');
        elsif rising_edge(CLK) then
            if tmp=x"9" then
                tmp <= (others => '0');
            else
                tmp <= tmp+'1';
            end if;
        end if;
    end process;
    Q <= tmp;
end BCD0_9 ; -- BCD0_9