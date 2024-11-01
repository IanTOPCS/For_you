library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Div_100hv is
    port(
        clk:in std_logic;
        clk100hz:out std_logic
    );
end Div_100hv;

architecture Div_100hv of Div_100hv is
    signal cnt:std_logic_vector(18 downto 0);
begin
    process(clk)
    begin
        if(rising_edge(clk))then
            if cnt < 499999 then
                cnt <= cnt + '1';
            else
                cnt <= (others => '0')
            end if;
        end if;
    end process;
    clk100hz <= cnt(18);
end Div_100hv;