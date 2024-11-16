library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity fab is
    port(
        X:in std_logic_vector(9 downto 0);
        start:in std_logic;
        clk:in std_logic;
        HEX0, HEX1, HEX2, HEX3:out std_logic_vector(6 downto 0)
    );
end fab;

architecture behavior of fab is
    component mul_nn is                                                 -- 上次的乘法電路，懶惰蟲想吃老本：Ｐ
        generic(number:integer range 1 to 32);
        port(
            X:in std_logic_vector(number-1 downto 0);                                                                                                                
            Y:in std_logic_vector(number-1 downto 0);
            Ans:out std_logic_vector(2*number-1 downto 0)                                                                                          
        );
    end component;

    component div_1s is                                                 --  除頻器
        port(
            clk:in std_logic;
            clk_out:out std_logic:='0'
        );
    end component;

    component decoder_7seg is
        PORT(
                BCD:in std_logic_vector(3 downto 0);
                HEX:out std_logic_vector(6 downto 0)
                );
    end component;

    component digits is
        port(
                BIN:in integer range 0 to 9999;
                num3: out integer range 0 to 9;
                num2: out integer range 0 to 9;
                num1: out integer range 0 to 9;
                num0: out integer range 0 to 9		
                );
                
    end component;

    component digits_large is                                           -- 位數大的恐怖，經過計算，最多12位顯示，13會爆出int range
        port(   
                BIN:in integer range 0 to 999999999;
                num11:out integer range 0 to 9;
                num10:out integer range 0 to 9;
                num9: out integer range 0 to 9;
                num8: out integer range 0 to 9;
                num7: out integer range 0 to 9;
                num6: out integer range 0 to 9;
                num5: out integer range 0 to 9;
                num4: out integer range 0 to 9;
                num3: out integer range 0 to 9;
                num2: out integer range 0 to 9;
                num1: out integer range 0 to 9;
                num0: out integer range 0 to 9		
                );            
    end component;

    signal clk_out:std_logic;                                           -- 除頻器輸出
    signal ans:std_logic_vector(29 downto 0):=(others => '0');          -- 最多30 bits 可以容納12的階層顯示
    signal sor:std_logic_vector(29 downto 0):=(others => '0');


    type INT_array is Array (0 to 3) of integer range 0 to 9;
    type INT_array_ans is Array (0 to 11) of integer range 0 to 9;
    type ans_array is Array (0 to 12) of std_logic_vector(59 downto 0);
	type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
	signal num1: INT_array;											    -- 來源每位數轉換的整數
	signal show:LOGIC_array;											-- 顯示結果
    signal num:INT_array_ans;
    signal dp:std_logic_vector(3 downto 0):=(others => '1');            -- 小數點輪播
    signal tmp_ans:ans_array;
begin
    tmp_ans(0) <= "000000000000000000000000000000000000000000000000000000000001";                       -- 初始狀態
    div: div_1s port map(clk,clk_out);
    sor <= conv_std_logic_vector(conv_integer(X),30);                                                   -- 因為不知道X幾bit，先轉整數，再轉固定 30 bits
    multiple:for i in 1 to 12 generate                                                                  -- 想偷懶~但問題卡在這裡，死掉惹：(
        mul: mul_nn generic map(30) port map(tmp_ans(i-1)(29 downto 0), conv_std_logic_vector(i, 30), tmp_ans(i));
    end generate multiple;
    ans <= tmp_ans(conv_integer(sor))(29 downto 0);                                                      -- 將最後的答案輸出

    U1:digits port map(conv_integer(sor), num1(3), num1(2), num1(1), num1(0));                          -- 來源每位數
    U2:digits_large port map(conv_integer(ans), num(11), num(10), num(9), num(8), num(7), num(6), num(5), num(4), num(3), num(2), num(1), num(0));-- 結果每位數

    process(start, clk)                                               
    begin
        if (start = '0') then                                               -- 輸入來源
            show(0) <= conv_std_logic_vector(num1(0),4);
            show(1) <= conv_std_logic_vector(num1(1),4);
            show(2) <= conv_std_logic_vector(num1(2),4);
            show(3) <= conv_std_logic_vector(num1(3),4);
            dp <= "1000";
        elsif(start = '1') then                                             -- 開始輪播答案
            if (rising_edge(clk_out)) then                                 
                if (dp = "1000") then                                       -- 共陽接角，亮一顆小點(最低四位結果)
                    show(0) <= conv_std_logic_vector(num(0),4);
                    show(1) <= conv_std_logic_vector(num(1),4);
                    show(2) <= conv_std_logic_vector(num(2),4);
                    show(3) <= conv_std_logic_vector(num(3),4);
                    dp <= "1110";                                           -- 迭代下一個輸出結果
                elsif(dp = "1110") then                                     -- 共陽接角，亮兩顆小點(中間四位結果)
                    show(0) <= conv_std_logic_vector(num(4),4);
                    show(1) <= conv_std_logic_vector(num(5),4);
                    show(2) <= conv_std_logic_vector(num(6),4);
                    show(3) <= conv_std_logic_vector(num(7),4);
                    dp <= "1100";
                elsif(dp = "1100") then                                     -- 共陽接角，亮三顆小點(最高四位結果)
                    show(0) <= conv_std_logic_vector(num(8),4);
                    show(1) <= conv_std_logic_vector(num(9),4);
                    show(2) <= conv_std_logic_vector(num(10),4);
                    show(3) <= conv_std_logic_vector(num(11),4);
                    dp <= "1000";
                end if;
            end if;
        end if;
    end process;

    HEX0_part:decoder_7seg port map(show(0),HEX0);  						-- 轉換數值成七段顯示器
	HEX1_part:decoder_7seg port map(show(1),HEX1);
	HEX2_part:decoder_7seg port map(show(2),HEX2);
	HEX3_part:decoder_7seg port map(show(3),HEX3);

end behavior;