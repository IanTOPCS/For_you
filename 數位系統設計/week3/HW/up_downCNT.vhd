library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity up_downCNT is
    port(
        up_clk:in std_logic;
        down_clk:in std_logic;
        RESET:in std_logic;
        ans:out std_logic_vector(3 downto 0)
    );
end up_downCNT;

architecture up_downCNT of up_downCNT is
    signal cnt:std_logic_vector(3 downto 0);
    signal clk:std_logic;
	 signal last_up:std_logic;
	 signal last_down:std_logic;
begin
	 
    
    clk <= up_clk or down_clk;
    process(RESET, clk)
    begin
        if RESET = '0' then
            cnt <= "0000";
        elsif rising_edge(clk) then
            if down_clk='0' and last_down='1' then      --如果上一次的我跟現在的我不一樣，就動作
                cnt <= cnt - '1';
            else
                cnt <= cnt + '1';
            end if;
            last_up <= up_clk;                          --紀錄上一次正元觸發紀錄
            last_down <= down_clk;
        end if;
    end process;
    ans <= cnt;
end up_downCNT;