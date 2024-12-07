library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;


entity Registers is
	port(
			clk:in std_logic;
			Reset:in std_logic;
			RegWrite:in std_logic;
			Read_register1:in integer range 0 to 31;
			Read_register2:in integer range 0 to 31;
			Write_register:in integer range 0 to 31;
			Write_data:in std_logic_vector(31 downto 0);
			Read_data1:out std_logic_vector(31 downto 0);
			Read_data2:out std_logic_vector(31 downto 0)
		 );
end Registers;

architecture Registers of Registers is

	type reg_array is array (0 to 31)of std_logic_vector( 31 downto 0 ); 
	signal reg_files : reg_array;
begin

	Read_data1 <= reg_files(Read_register1);
	Read_data2 <= reg_files(Read_register2);
	
	process(clk,Reset)
	begin
		if Reset = '0' then
			for i in 0 to 31 loop
				 reg_files(i) <= (others => '0');
			end loop; 
		elsif clk'event and clk = '1' then
			if RegWrite = '1' then 
				reg_files(Write_register) <= Write_data;
			end if;
		end if;
	end process;	
			
	


end Registers;	

	 