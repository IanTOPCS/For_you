library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Sign_extend is
	port(
			Inst15_0:in std_logic_vector(15 downto 0);
			Extendout:out std_logic_vector(31 downto 0)
 		 );
end Sign_extend;
architecture Sign_extend of Sign_extend is

begin

	Extendout <= "0000000000000000"&Inst15_0 when Inst15_0(15) = '0' else
				 "1111111111111111"&Inst15_0;	
	
end Sign_extend;