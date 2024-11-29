library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Instruction_memory is
	port(
			Read_address:in integer range 0 to 63;
			Instruction:out std_logic_vector(31 downto 0)
 		 );
end Instruction_memory;
architecture Instruction_memory of Instruction_memory is
	type mem_array is array (0 to 63)of std_logic_vector( 31 downto 0 ); 
	signal memory : mem_array := (
									x"fc000000",x"fc010007",x"ac010000",x"fc010004",x"ac010004",x"fc010058", x"ac010008", x"fc010040",x"ac01000c",x"fc010022",
									x"ac010010",x"fc01000a",x"ac010014",x"fc01005b",x"ac010018",x"fc010008",x"ac01001c",x"fc01003e",
									x"ac010020",x"fc010009",x"ac010024",x"fc020004",x"fc030000",x"fc040024", x"fc070000",x"8c050000",
									x"0065302a",x"10c70001",x"00a71820",x"f8030000",x"10040002",x"00020020",x"08000018",x"f8030000",
									x"f4000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
									x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000");		
begin

	Instruction <= memory(Read_address); 
	
				
						
end Instruction_memory;