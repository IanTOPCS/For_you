library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Instruction_memory is			-- 指令存放地
	port(
			Read_address:in integer range 0 to 63;
			Instruction:out std_logic_vector(31 downto 0)
 		 );
end Instruction_memory;
architecture Instruction_memory of Instruction_memory is
	type mem_array is array (0 to 63)of std_logic_vector( 31 downto 0 ); 
	signal memory : mem_array := (
									x"fc010001",x"fc020000",x"fc03000a",x"fc040013",x"fc070004",x"ac430000", x"10640003", x"00611820",x"00471020",x"08000005",
									x"fc060000",x"fc020000",x"8c450000",x"f8050000",x"f8060000",x"00c53020",x"00471020",x"10a40001",
									x"0800000c",x"f8060000",x"f4000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000");		
begin

	Instruction <= memory(Read_address); 
	
				
						
end Instruction_memory;