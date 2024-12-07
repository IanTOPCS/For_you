library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Data_memory is
	port(
			clk:in std_logic;
			Address:in integer range 0 to 63;
			Write_data:in std_logic_vector(31 downto 0);
			MemWrite:in std_logic;
			MemRead:in std_logic;
			Read_data:out std_logic_vector(31 downto 0)
 		 );
end Data_memory;
architecture Data_memory of Data_memory is
	type mem_array is array (0 to 63)of std_logic_vector( 31 downto 0 ); 
	signal memory : mem_array;		
begin

	Read_data <= memory(Address) when MemRead = '1' else
	          "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
	process(clk)
	begin
		if clk'event and clk = '1' then
			if MemWrite = '1' then
				memory(Address) <= Write_data;
			end if;
		end if;
	end process;	




end Data_memory;