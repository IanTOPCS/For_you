library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Add_32bit is
	port(
			A:in std_logic_vector(31 downto 0);
			B:in std_logic_vector(31 downto 0);
			Result:out std_logic_vector(31 downto 0)
 		 );
end Add_32bit;
architecture Add_32bit of Add_32bit is

begin

	Result <= A + B;	
	
end Add_32bit;