library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity upBCD_4bits is
    port(
        clk:in std_logic;                                       -- 時脈
        reset:in std_logic;                                     -- 重置
        stop_pos:in std_logic;                                  -- 暫停計數
        casout:out std_logic;                                   -- 進位
        Q:out std_logic_vector(3 downto 0)                      -- 結果
    );
end upBCD_4bits;

architecture upBCD_4bits of upBCD_4bits is
    signal cnt:std_logic_vector(3 downto 0):=(others => '0');
    signal flag:std_logic:='0';                                 -- 進位(避免最開始的 0)
begin
    process(clk, reset)
    begin
        if(reset = '0') then
            cnt <= x"0";
            flag <= '0';
        elsif stop_pos = '0' then
            cnt <= cnt;
            flag <= flag;
        elsif rising_edge(clk) then
            if(cnt = x"9")then                                  -- BCD 計數
                cnt <= x"0";
                flag <= '1';
            else
                cnt <= cnt + '1';
                flag <= '0';
            end if;
        end if;
    end process;
    Q <= cnt;
    process(cnt)
    begin
        if ((cnt = x"0") and (flag = '1')) then                 -- 進位指示
            casout <= '1';
        else
            casout <= '0';
        end if;
    end process;
end upBCD_4bits;