library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity downBCD_4bits is
    port(
        casin:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end downBCD_4bits;

architecture downBCD_4bits of downBCD_4bits is
    signal cnt:std_logic_vector(3 downto 0);
begin
    process(clk, reset)
    begin
        if(reset = '0') then
            cnt <= x"0";
        elsif rising_edge(clk) then
            if(casin = '1')then
                if(cnt = x"0")then
                    cnt <= x"9";
                else
                    cnt <= cnt - '1';
                end if;
            end if;
        end if;
    end process;
    Q <= cnt;
    process(cnt, casin)
    begin
        if ((cnt = x"0") and (casin = '1')) then
            casout <= '1';
        else
            casout <= '0';
        end if;
    end process;
end downBCD_4bits;