library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity BCD0_99 is
    port(
        CLK:in std_logic;
        RESET:in std_logic;
        up_down:in std_logic;
        Q:out std_logic_vector(7 downto 0)
    );
end BCD0_99;

architecture BCD0_99 of BCD0_99 is
    signal tmp:std_logic_vector(7 downto 0);
begin
    process(CLK, RESET)
    begin
        if RESET='0' then
            if up_down='1' then
                tmp <= "1001" & "1001";
            elsif up_down='0' then
                tmp <= (others => '0');
            end if;
        elsif rising_edge(CLK) then
            if up_down='0' then                                 --遇到0上數
                if tmp(7 downto 4)=x"9" then
                    tmp(7 downto 4) <= x"0";
                elsif tmp(3 downto 0)=x"9" then
                    tmp(7 downto 4) <= tmp(7 downto 4)+'1';
                end if;
                if tmp(3 downto 0)=x"9" then
                    tmp(3 downto 0) <= x"0";
                else
                    tmp(3 downto 0) <= tmp(3 downto 0)+'1';
                end if;
            elsif up_down='1' then                              --遇到1下數
                if tmp(7 downto 4)=x"0" then
                    tmp(7 downto 4) <= x"9";
                elsif tmp(3 downto 0)=x"0" then
                    tmp(7 downto 4) <= tmp(7 downto 4)-'1';
                end if;
                if tmp(3 downto 0)=x"0" then
                    tmp(3 downto 0) <= x"9";
                else
                    tmp(3 downto 0) <= tmp(3 downto 0)-'1';
                end if;
            end if;
        end if;
    end process;
    Q <= tmp;
end BCD0_99 ; -- BCD0_99