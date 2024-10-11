library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity downBCD_4bits is
    port(
        casin:in std_logic;                             -- 可否工作
        clk:in std_logic;                               -- 時脈
        reset:in std_logic;                             -- 歸零
        casout:out std_logic;                           -- 進位輸出
        Q:out std_logic_vector(3 downto 0)
    );
end downBCD_4bits;

architecture downBCD_4bits of downBCD_4bits is
    signal cnt:std_logic_vector(3 downto 0);
begin
    process(clk, reset)
    begin
        if(reset = '0') then
            cnt <= x"0";                                -- 強制歸零
        elsif rising_edge(clk) then
            if(casin = '1')then                         -- 可以工作
                if(cnt = x"0")then                      -- BCD計數器規則
                    cnt <= x"9";
                else
                    cnt <= cnt - '1';                   -- 可以下數
                end if;
            end if;
        end if;
    end process;
    Q <= cnt;
    process(cnt, casin)
    begin
        if ((cnt = x"0") and (casin = '1')) then       -- 如果是零，應該回到九，BCD計數器規則
            casout <= '1';
        else
            casout <= '0';
        end if;
    end process;
end downBCD_4bits;