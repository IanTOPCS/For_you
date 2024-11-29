library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity ALU is
	port(
			A:in std_logic_vector(31 downto 0);
			B:in std_logic_vector(31 downto 0);
			Operation:in std_logic_vector(3 downto 0);
			ALUresult:out std_logic_vector(31 downto 0);
			Zero:out std_logic
			
			);
end ALU;
architecture ALU of ALU is
		signal tmp: std_logic_vector(31 downto 0);
begin

	tmp <=  	A or B when Operation = "0000" else
				A and B when Operation = "0001" else
				A + B when Operation = "0010" else
				A - B when Operation = "0110" else
				A nor B when Operation = "1100" else
				x"00000001" when Operation = "0111" and A < B else
				x"00000000" when Operation = "0111" else
				x"FFFFFFFF";
				
	ALUresult <= tmp;
	Zero <= '1' when tmp = x"00000000" else
			  '0';



end ALU;

			