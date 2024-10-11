library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity up_downBCD_4bits is
    port(
        casin:in std_logic;
        up_down:in std_logic;
        clk:in std_logic;
        reset:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end up_downBCD_4bits;

architecture up_downBCD_4bits of up_downBCD_4bits is
    signal cnt:std_logic_vector(3 downto 0);
begin
    process(reset, clk)
    begin
        if(reset = '0') then
            if (up_down = '1') then                         -- 定義 1 上數
                cnt <= x"0";
            elsif(up_down = '0') then                       -- 定義 0 下數
                cnt <= x"9";
            end if;
        elsif(rising_edge(clk)) then
            if(casin = '1') then                            -- 1 才可以工作
                if(up_down = '1') then                      -- 規定上數
                    if(cnt = x"9") then                     -- 如果上數 9 下一個要是 0 
                        cnt <= x"0";
                    else
                        cnt <= cnt + '1';
                    end if;
                elsif(up_down = '0') then                   -- 規定下數
                    if(cnt = x"0") then                     -- 如果下數 0 下一個要是 1 
                        cnt <= x"9";
                    else
                        cnt <= cnt - '1';
                    end if;
                end if;
            end if;
        end if;
    end process;
    Q <= cnt;
    process(cnt, casin, up_down)
    begin
        if(casin = '1') then
            if((up_down = '1') and (cnt = x"9"))then      -- 如果上數到9，就該進位
                casout <= '1';
            elsif((up_down = '0') and (cnt = x"0"))then
                casout <= '1';
            else
                casout <= '0';
            end if;
        else
            casout <= '0';
        end if;
    end process;
end up_downBCD_4bits ;