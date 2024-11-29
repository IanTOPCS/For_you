library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity ALUControl is
	port(
			ALUOp:in std_logic_vector(1 downto 0);
			Inst5_0:in std_logic_vector(5 downto 0);  --func of R type inst
			Operation:out std_logic_vector(3 downto 0)
		);
end ALUControl;
architecture ALUControl of ALUControl is
begin

	Operation <= "0010" when ALUOp = "00" else  -- lw sw
					 "0110" when ALUOp = "01" else  -- beq
					 "0010" when ALUOp = "10" and Inst5_0 = "100000" else -- (+)
					 "0110" when ALUOp = "10" and Inst5_0 = "100010" else -- (-)
					 "0000" when ALUOp = "10" and Inst5_0 = "100100" else -- (or)
					 "0001" when ALUOp = "10" and Inst5_0 = "100101" else -- (and)
					 "0111" when ALUOp = "10" and Inst5_0 = "101010" else -- (slt)
                "1111";
					 
end ALUControl;