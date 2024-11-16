library ieee;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_1164.all;


entity digits_large is
port(
		BIN:in integer range 0 to 999999999;    -- 最多9位數，且最高位是2，九個九不可能超過輸入上限，且範圍依然在 int 限制內  
        num11:out integer range 0 to 9:=0;
        num10:out integer range 0 to 9:=0;
        num9: out integer range 0 to 9:=0;
        num8: out integer range 0 to 9:=0;
        num7: out integer range 0 to 9:=0;
        num6: out integer range 0 to 9:=0;
        num5: out integer range 0 to 9:=0;
        num4: out integer range 0 to 9:=0;
		num3: out integer range 0 to 9:=0;
		num2: out integer range 0 to 9:=0;
		num1: out integer range 0 to 9:=0;
		num0: out integer range 0 to 9:=0		
		);
		
end digits_large;

architecture digits of digits_large is
begin
    num11<= 0;                              -- 爆出int range，不可能會輸出數字，必為0
    num10<= 0;                              -- 爆出int range，不可能會輸出數字，必為0
    num9 <= 0;                              -- 爆出int range，不可能會輸出數字，必為0
    num8 <= BIN/100000000;
    num7 <= (BIN/10000000) mod 10;
    num6 <= (BIN/1000000) mod 10;
    num5 <= (BIN/100000) mod 10;
    num4 <= (BIN/10000) mod 10;
	num3 <= (BIN/1000) mod 10;				-- 算出千位數
	num2 <= (BIN/100) mod 10;				-- 算出百位數
	num1 <= (BIN/10) mod 10; 				-- 算出十位數
	num0 <= BIN mod 10; 					-- 求出個位數
end digits;