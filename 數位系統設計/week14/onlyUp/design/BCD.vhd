library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity BCD is
    port(
        clk:in std_logic;               -- 綁定 50M 時脈
        bot:in std_logic;               -- 綁定 bot 0 按鈕(reset)
        botStop:in std_logic;           -- 綁定 bot 1 按鈕(stop)
        
        clkin:in std_logic;             -- 接收時脈(BCD counter)
        reset:in std_logic;             -- 兩塊板子接收 reset
        stop_pos:in std_logic;          -- 接收 stop 信號
        clkout:out std_logic;           -- 發出進位時脈
        clkin1:out std_logic;           -- 發出除頻結果, 讓第一塊板子拉線接收
        stop1, stop2:out std_logic;     -- 接收 botStop, 發出 stop 信號, 拉線讓兩塊板子暫停
        rstout1, rstout2:out std_logic; -- 接收 bot, 發出 reset 信號, 拉線讓兩塊板子重置
        Hex0,Hex1,Hex2,Hex3:out std_logic_vector(6 downto 0)
    );
end entity;

architecture BCD of BCD is
    component upBCD_16bits is
        port(
            clk:in std_logic;
            reset:in std_logic;
            stop_pos:in std_logic;
            casout:out std_logic;
            Q:out std_logic_vector(15 downto 0)
        );
    end component;

    component decoder_7seg is
        PORT(
            BCD:in std_logic_vector(3 downto 0);
            HEX:out std_logic_vector(6 downto 0)
        );
    end component;
    signal ans:std_logic_vector(15 downto 0);       -- BCD counter 結果
    signal cnt:integer range 0 to 50000000:=0;      -- 除頻器(範圍 1 秒 -> 1/10000 秒)
    signal clkCnt:std_logic:='0';                   -- 除頻後 clock
    signal waste:std_logic:='0';                    -- stop 按下後，啥都不要做就是暫停
begin
    rstout1 <= bot;
    rstout2 <= bot;

    stop1 <= botStop;
    stop2 <= botStop;

    process(clk)
    begin
        if(rising_edge(clk)) then
            if (cnt < 4999) then
                cnt <= cnt + 1;
                clkCnt <= '0';
            else
                clkCnt <= '1';
                cnt <= 0;
            end if;
        end if;
    end process;
    clkin1 <= clkCnt;                             -- 第一塊板子拉線接除頻結果
                                                  -- 第二塊板子拉線接收第一塊板子的clkout

    upBCD:upBCD_16bits port map(clkin, reset, stop_pos, clkout, ans);

    -- 接七段顯示器
    decoder0:decoder_7seg port map(ans(3 downto 0), Hex0);
    decoder1:decoder_7seg port map(ans(7 downto 4), Hex1);
    decoder2:decoder_7seg port map(ans(11 downto 8), Hex2);
    decoder3:decoder_7seg port map(ans(15 downto 12), Hex3);
end BCD;