library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity mul_nbit_hex is
	PORT(
			X:in std_logic_vector(3 downto 0);							-- 資料來源
			Y:in std_logic_vector(3 downto 0);							-- 資料來源
			sw:in std_logic_vector(1 downto 0);
			bt, bt2:in std_logic;										-- bt 為基本題按鈕，bt2 為加法題按鈕
			HEX0,HEX1,HEX2,HEX3:out std_logic_vector(6 downto 0)		-- 七段顯示器結果
			);
end mul_nbit_hex;

architecture mul_nbit_hex of mul_nbit_hex is

		component mul_nn is
			generic(number :integer range 1 to 32);  
			PORT(
					X:in std_logic_vector(number-1 downto 0);
					Y:in std_logic_vector(number-1 downto 0);
					Ans:out std_logic_vector(2*number-1 downto 0)
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

		component add is
			port(
				X:in std_logic_vector(3 downto 0);
				Y:in std_logic_vector(3 downto 0);
				Q:out std_logic_vector(7 downto 0)
			);
		end component;
		
		component decoder_7seg is
			PORT(
					BCD:in std_logic_vector(3 downto 0);
					HEX:out std_logic_vector(6 downto 0)
					);
		end component;		
		

		type INT_array is Array (0 to 3) of integer range 0 to 9;
		type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
		signal num,num1,num2: INT_array;											-- 存放乘法每位數轉換的整數		
		signal P, f0, f1, f2, f3:std_logic_vector(7 downto 0);						-- 存放運算結果
		signal f4:std_logic_vector(15 downto 0);									-- 8 bits * 8 bits = 16 bits
		signal show:LOGIC_array;													-- 存放待轉換七段顯示器的數值

begin

	FUN0: add port map(X, Y, f0);													-- 00 為加法
	FUN1: mul_nn generic map(4) port map(X, Y, f1);									-- 01 為乘法
	FUN2: mul_nn generic map(4) port map(X, X, f2);									-- 10 為X的平方
	FUN3: mul_nn generic map(4) port map(Y, Y, f3);									-- 11 為Y的平方
	FUN4: mul_nn generic map(8) port map(f2, f3, f4);								-- 當 bt2 按下(0)時，為 ((X*X) * (Y*Y))

	process(sw, bt2)																-- 偵測bt2, sw。因 bt 只決定顯示結果 or 撥到的數字，但這裡只做P的運算結果，而非顯示結果
	begin
		if (bt2 = '0') then
			p <= f4(7 downto 0);													-- 乘法結果溢位，取末 8 bits
		else 
			if (sw = "00") then
				p <= f0;
			elsif (sw = "01") then
				p <= f1;
			elsif (sw = "10") then
				p <= f2;
			elsif (sw = "11") then
				p <= f3;
			end if;
		end if;
	end process;

	U2:digits port map(Conv_integer(P),num(3),num(2),num(1),num(0));				-- num 為 運算結果(每位數)轉換的整數(按下按鈕的時候)

	U3:digits port map(Conv_integer(X),num1(3),num1(2),num1(1),num1(0));			-- num1 為 本身來源(每位數)的整數(沒按按鈕的時候)
	U4:digits port map(Conv_integer(Y),num2(3),num2(2),num2(1),num2(0));			-- num2 為 本身來源(每位數)的整數(沒按按鈕的時候)

	show(0) <= conv_std_logic_vector(num(0),4) when (bt = '0')or(bt2 = '0') else	-- 按下按鈕(0)顯示運算結果，不然(1)顯示撥到的數字
			conv_std_logic_vector(num1(0),4);
					
	show(1) <= conv_std_logic_vector(num(1),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num1(1),4);
				
	show(2) <= conv_std_logic_vector(num(2),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num2(0),4);

	show(3) <= conv_std_logic_vector(num(3),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num2(1),4);		

	HEX0_part:decoder_7seg port map(show(0),HEX0);  								-- 轉換數值成七段顯示器
	HEX1_part:decoder_7seg port map(show(1),HEX1);
	HEX2_part:decoder_7seg port map(show(2),HEX2);
	HEX3_part:decoder_7seg port map(show(3),HEX3);


end mul_nbit_hex;