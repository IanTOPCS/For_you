library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity div_1s is
    port(
        clk:in std_logic;
        clk_out:out std_logic:='0'
    );
end div_1s;

architecture bhv of div_1s is
    signal cnt:std_logic_vector(31 downto 0):=(others => '0');      -- 絕對夠用的計算存放空間，並歸零
    signal clk_tmp:std_logic:='0';
begin
    process(clk)
    begin
        if(rising_edge(clk)) then                           -- 累加時脈
            if(cnt = 50000000) then                         -- 50MHZ = MSB 為 1s
                cnt <= (others => '0');                     -- 歸零
                clk_tmp <= not clk_tmp;                     -- 製造除頻的clk
            else
                cnt <= cnt + '1';                           -- 小於目標就繼續累加時脈
            end if;
        end if;
    end process;
    clk_out <= clk_tmp;                                     -- 輸出
end bhv;