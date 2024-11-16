library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity div is
	port(
			clk:in std_logic;                                                               -- 計算除法需要的clk，此題最多10次
			XY:in std_logic_vector(9 downto 0);                                             -- 選擇輸入
			sw0:in std_logic;                                                               -- 輸入被除數
			sw1:in std_logic;                                                               -- 輸入除數
			start:in std_logic;                                                             -- 開始除法
			HEX0,HEX1,HEX2,HEX3:out std_logic_vector(6 downto 0)                            -- 顯示 被除數、除數、(餘數、商)
			);
end div;

architecture MUL_ver1 of div is
        component digits is
        port(
                BIN:in integer range 0 to 9999;
                num3: out integer range 0 to 9;
                num2: out integer range 0 to 9;
                num1: out integer range 0 to 9;
                num0: out integer range 0 to 9		
                );
                
        end component;


        component decoder_7seg is
            PORT(
                    BCD:in std_logic_vector(3 downto 0);
                    HEX:out std_logic_vector(6 downto 0)
                    );
        end component;

    signal cnt:std_logic_vector(3 downto 0);                                                -- 指撥開關最多10個，且除法做bits次，最多10次
    signal cnt1:std_logic_vector(25 downto 0);                                              -- 除頻器(延長顯示時間)
    signal divisor, dividen:std_logic_vector(9 downto 0);                                   -- 除數、被除數
    signal remainder:std_logic_vector(19 downto 0);                                         -- 左(餘)右(商)
    

    type INT_array is Array (0 to 3) of integer range 0 to 9;
    type INT_array_large is Array (0 to 7) of integer range 0 to 9;		
    type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
    signal divisor_num, dividen_num: INT_array;	                                            -- 除數、被除數(顯示數字)
    signal remainder_num: INT_array_large;	                                                -- 餘數、商(顯示數字)
    signal show:LOGIC_array;                                                                -- 顯示數字(轉成七段顯示器)
    signal flag:std_logic;                                                                  -- 接受start，確定開始除法
    signal dp:std_logic_vector(3 downto 0);                                                 -- 小數點輪播(表示餘數)
begin
	process(clk)                                                                            -- 除頻器   
	begin
		if clk'event and clk = '1' then
			cnt1 <= cnt1 + 1;
		end if;
	end process;

	
	process(sw0)                                                                            -- 確定被除數
	begin
		if sw0 = '0' then
			dividen <= XY;
		end if;
	end process;
	
	process(sw0,start)                                                                      -- 開始除法   
	begin
		if sw0 = '0' and start = '1' then
			flag <= '0';
		elsif sw0 = '1' and start = '0' then	
			flag <= '1';
		end if;
	end process;	
		
	process(sw1)                                                                            -- 確定除數
	begin
		if sw1 = '0' then
            divisor <= XY;
		end if;
	end process;
	
	process(clk,start)                                                                      -- 除法開始(以 10 clk 為一次週期)，於確認start信號
	variable remainder_reg:std_logic_vector(19 downto 0);
	variable divisor_reg, tmp:std_logic_vector(9 downto 0);	                                -- 以 tmp 存放相減結果，避免小於零復原動作
	begin
		if start = '0' then                                                                 -- 按下按鈕，先做初始化動作
			tmp := (others => '0');
            divisor_reg := divisor;
            remainder_reg := ("000000000" & dividen & '0');                                 -- 補零、左移 1 bit
			cnt <= "0000";
		elsif (rising_edge(clk)) then
			if cnt < 10 then
                cnt <= cnt + 1;
                tmp := remainder_reg(19 downto 10) - divisor_reg;                           -- 相減
                if(tmp(9) = '0') then                                                       -- 最高位數判斷是否大於零
                    remainder_reg := tmp(8 downto 0) & remainder_reg(9 downto 0) & '1';     -- 大於零，左移併補一
                else
                    remainder_reg := remainder_reg(18 downto 0) & '0';                      -- 以 tmp 避免還原，左移補零
                end if;
			elsif (cnt = 10) then
                cnt <= cnt +1;                                                              -- 確保 cnt = 10 只會執行一次(餘數只會右移一次)
                remainder_reg := '0' & remainder_reg(19 downto 11) & remainder_reg(9 downto 0);     -- 左半右移
			end if;
		end if;	
        remainder <= remainder_reg;                                                         -- 於 process 結束前回填 variable 至 signal
	end process;
    
    U0:digits port map(Conv_integer(remainder(19 downto 10)),remainder_num(7),remainder_num(6),remainder_num(5),remainder_num(4));	-- 將餘數轉成十進位
    U1:digits port map(Conv_integer(remainder(9 downto 0)),remainder_num(3),remainder_num(2),remainder_num(1),remainder_num(0));    -- 將商數轉成十進位
    U2:digits port map(Conv_integer(dividen),dividen_num(3),dividen_num(2),dividen_num(1),dividen_num(0));	                        -- 將被除數轉成十進位
    U3:digits port map(Conv_integer(divisor),divisor_num(3),divisor_num(2),divisor_num(1),divisor_num(0));	                        -- 將除數轉成十進位

    show(0) <= conv_std_logic_vector(dividen_num(0),4) when sw0 = '0' else                                                          -- 按下 sw0 顯示被除數十進位
                conv_std_logic_vector(divisor_num(0),4) when sw1 = '0' else	                                                        -- 按下 sw1 顯示除數十進位
            conv_std_logic_vector(remainder_num(0),4)  when cnt1(25) = '0' and flag = '1' else                                      -- 餘數十進位(配合除頻器延長顯示)
                conv_std_logic_vector(remainder_num(4),4)  when cnt1(25) = '1' and flag = '1' else                                  -- 商數十進位(配合除頻器延長顯示)
                "1111";
                
    show(1) <= conv_std_logic_vector(dividen_num(1),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(1),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(1),4)  when cnt1(25) = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(5),4)  when cnt1(25) = '1' and flag = '1' else
                "1111";

    show(2) <= conv_std_logic_vector(dividen_num(2),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(2),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(2),4)  when cnt1(25) = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(6),4)  when cnt1(25) = '1' and flag = '1' else
                
                "1111";

    show(3) <= conv_std_logic_vector(dividen_num(3),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(3),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(3),4)  when cnt1(25) = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(7),4)  when cnt1(25) = '1' and flag = '1' else
                "1111";			  
                
    dp <= (others => '0') when (flag = '1' and cnt1(25) = '1') else (others => '1');                                                 -- 餘數小數點(配合除頻器延長顯示)

    HEX0_part:decoder_7seg port map(show(0),HEX0);                                                                                   -- 將十進位數字轉成七段顯示
    HEX1_part:decoder_7seg port map(show(1),HEX1);
    HEX2_part:decoder_7seg port map(show(2),HEX2);
    HEX3_part:decoder_7seg port map(show(3),HEX3);			
end MUL_ver1;			