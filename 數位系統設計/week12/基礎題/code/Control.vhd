library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity Control is
	port(
			Inst31_26:in std_logic_vector(5 downto 0);
			Jump:out std_logic;
			Halt:out std_logic;
			RegImport:out std_logic;
			RegOutport:out std_logic;
			RegDst:out std_logic;
			Branch:out std_logic;
			MemRead:out std_logic;
			MemtoReg:out std_logic;
			ALUOp:out std_logic_vector(1 downto 0);
			MemWrite:out std_logic;
			ALUSrc:out std_logic;
			RegWrite:out std_logic
		);
end Control;
architecture Control of Control is
	signal tmp:std_logic_vector(12 downto 0);
begin
	-- op code
	tmp <= "0000100100010" when inst31_26 = 0 else   	--R
	       "0000011110000" when inst31_26 = 35 else  	--lw
			 "0000010001000" when inst31_26 = 43 else  	--sw
			 "0000000000101" when inst31_26 = 4 else 	--beq
			 "0010000100011" when inst31_26 = 63 else   --RegImport
			 "0001000000011" when inst31_26 = 62 else	--RegOutportout	
			 "0100000000011" when inst31_26 = 61 else	--Halt	
			 "1000000000011" when inst31_26 = 2 else	--Jump				 
			 "0000000000000";
	Jump <= tmp(12);			 
	Halt <= tmp(11);
	RegImport <= tmp(10);
	RegOutport <= tmp(9);			 
			 
	RegDst <= tmp(8);
	ALUSrc <= tmp(7);
	MemtoReg <= tmp(6);
	RegWrite <= tmp(5);		 
	MemRead <= tmp(4);		
	MemWrite <= tmp(3);
	Branch <= tmp(2);
	ALUOp <= tmp(1 downto 0);
end Control;