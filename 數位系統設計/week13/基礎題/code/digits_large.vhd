library ieee;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_1164.all;


entity digits_large is
port(
		BIN:in integer range 0 to 99999999;
		num7: out integer range 0 to 9;
		num6: out integer range 0 to 9;
		num5: out integer range 0 to 9;
		num4: out integer range 0 to 9;			
		num3: out integer range 0 to 9;
		num2: out integer range 0 to 9;
		num1: out integer range 0 to 9;
		num0: out integer range 0 to 9		
		);
		
end digits_large;

architecture digits_large of digits_large is
begin

	num7 <= BIN /10000000;
	num6 <= (BIN /1000000) mod 10; 	
	num5 <= (BIN /100000) mod 10; 
	num4 <= (BIN /10000) mod 10; 
	num3 <= (BIN /1000) mod 10;
	num2 <= (BIN /100) mod 10; 	
	num1 <= (BIN /10) mod 10; 
	num0 <= BIN mod 10; 
	
	
end digits_large;