library ieee;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_1164.all;


entity digits is
port(
		BIN:in integer range 0 to 9999;
		num3: out integer range 0 to 9;
		num2: out integer range 0 to 9;
		num1: out integer range 0 to 9;
		num0: out integer range 0 to 9		
		);
		
end digits;

architecture digits of digits is
begin

	num3 <= BIN /1000;						-- 算出千位數
	num2 <= (BIN /100) mod 10;				-- 算出百位數
	num1 <= (BIN /10) mod 10; 				-- 算出十位數
	num0 <= BIN mod 10; 					-- 求出個位數
	
	
end digits;