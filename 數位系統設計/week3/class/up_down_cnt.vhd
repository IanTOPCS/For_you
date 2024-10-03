library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity up_down_cnt is
    port(
        CLK:in std_logic;
        up_down:in std_logic;
        RESET:in std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end up_down_cnt;

architecture up_donw_cnt of up_down_cnt is
    signal tmp:std_logic_vector(3 downto 0);
begin
    process(CLK, RESET)
    begin
        if RESET='0' then
            tmp <= (others => '0');
        elsif rising_edge(CLK) then
            if up_down='1' then
                tmp <= tmp-'1';
            elsif up_down='0' then
                tmp <= tmp+'1';
            end if;
        end if;
    end process;
    Q <= tmp;
end up_donw_cnt ; -- up_donw_cnt