library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Instruction_memory is
	port(
			Reset:in std_logic;
			Read_address:in integer range 0 to 63;
			Instruction:out std_logic_vector(31 downto 0)
 		 );
end Instruction_memory;
architecture Instruction_memory of Instruction_memory is
	type mem_array is array (0 to 63)of std_logic_vector( 31 downto 0 ); 
	signal memory : mem_array := (
											x"68000000",x"68000000",x"08000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",
											x"00000000",x"00000000",x"00000000",x"00000000",x"00000000",x"00000000");		
begin

			Instruction <= memory(Read_address); 

			process(Reset)
			begin
				if Reset = '0' then
				    memory(0) <= x"68000000";  -- 令第一個LED亮起
					memory(1) <= x"68000000";  -- 令第二個LED亮起
					memory(2) <= x"08000000";  -- 令第三個LED亮起，並跳回第一個指令

					for i in 3 to 63 loop
						memory(i) <= (others => '0');
					end loop;					
				end if;
			end process;
	
			
						
end Instruction_memory;