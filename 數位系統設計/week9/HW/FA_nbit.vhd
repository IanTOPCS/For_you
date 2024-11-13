library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity FA_nbit is
	generic(number :integer range 1 to 32 := 3);  
	PORT(
			A:in std_logic_vector(number-1 downto 0);
			B:in std_logic_vector(number-1 downto 0);
			cin:in std_logic;
			Q:out std_logic_vector(number-1 downto 0);
			cout:out std_logic
			);
end FA_nbit;

architecture FA_nbit of FA_nbit is
	signal tmp :std_logic_vector(number downto 0);		-- 比結果多 1bit，存放家完的進位
begin

	tmp <= ('0' & A) + B + cin;							-- 乘法每列結果相加需考慮上方列補零，對其下方列。(上方列LSB為答案LSB)
	Q <= tmp(number-1 downto 0);
	cout <= tmp(number);								-- 存入進位


end FA_nbit;