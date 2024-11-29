library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity MIPS is
	port(
			clk:in std_logic;
			Reset:in std_logic;
			--Input:in std_logic_vector(31 downto 0);
			PCout:out std_logic_vector(7 downto 0);
			ALUout:out std_logic_vector(31 downto 0);
			Instout:out std_logic_vector(31 downto 0);
			ALUopout:out std_logic_vector(3 downto 0);
			Output:out std_logic_vector(31 downto 0)
 		 );
end MIPS;
architecture MIPS of MIPS is

			component Registers is
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
			end component;

			component ALU is
				port(
						A:in std_logic_vector(31 downto 0);
						B:in std_logic_vector(31 downto 0);
						Operation:in std_logic_vector(3 downto 0);
						ALUresult:out std_logic_vector(31 downto 0);
						Zero:out std_logic
						
						);
			end component;

			component Data_memory is
				port(
						clk:in std_logic;
						Address:in integer range 0 to 63;
						Write_data:in std_logic_vector(31 downto 0);
						MemWrite:in std_logic;
						MemRead:in std_logic;
						Read_data:out std_logic_vector(31 downto 0)
					 );
			end component;

			component Instruction_memory is
				port( 
						Read_address:in integer range 0 to 63;
						Instruction:out std_logic_vector(31 downto 0)
					 );
			end component;

			component Sign_extend is
				port(
						Inst15_0:in std_logic_vector(15 downto 0);
						Extendout:out std_logic_vector(31 downto 0)
					 );
			end component;

			component Control is
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
			end component;

			component ALUControl is
				port(
						ALUOp:in std_logic_vector(1 downto 0);
						Inst5_0:in std_logic_vector(5 downto 0);
						Operation:out std_logic_vector(3 downto 0)
					);
			end component;

			component Add_32bit is
				port(
						A:in std_logic_vector(31 downto 0);
						B:in std_logic_vector(31 downto 0);
						Result:out std_logic_vector(31 downto 0)
					 );
			end component;

		signal Instruction:std_logic_vector(31 downto 0);
		signal Extendout:std_logic_vector(31 downto 0);
		signal Read_data1:std_logic_vector(31 downto 0);
		signal Read_data2:std_logic_vector(31 downto 0);
		
		signal ALUResult:std_logic_vector(31 downto 0);
		signal ALU_B:std_logic_vector(31 downto 0);
		signal Operation:std_logic_vector(3 downto 0);		
		signal Zero:std_logic;		
		

		signal Read_mem_data:std_logic_vector(31 downto 0);
		signal PC:std_logic_vector(31 downto 0);
		signal Jump,Halt,RegImport,RegOutport:std_logic;
		signal Branch,RegDst,MemRead,MemtoReg,MemWrite,ALUSrc,RegWrite:std_logic;
		signal ALUop:std_logic_vector(1 downto 0);

		signal Read_register1,Read_register2,Write_register:integer range 0 to 31;
		signal Write_data:std_logic_vector(31 downto 0);
		
		signal Add_32bit_A:std_logic_vector(31 downto 0);
		signal Add_32bit_B:std_logic_vector(31 downto 0);
		signal AddResult:std_logic_vector(31 downto 0);		

begin

--Program Counter	
	process(clk,reset)
	begin
		if reset = '0' then
			PC <= (others => '0');
		elsif clk'event and clk = '1' then
			if Branch = '1' and Zero = '1' then
				PC <= AddResult;
			elsif Jump = '1' then
			--else
				PC <= PC(31 downto 28)&Instruction(25 downto 0)&"00";				
			elsif Halt = '0' then
			--else
				PC <= PC + 4;
			end if;
		end if;
	end process;	
	
--Instruction Memory	

Inst_Memory_part:
Instruction_memory port map (conv_integer(PC(7 downto 2)),Instruction);



--Registers	
Read_register1 <= conv_integer(Instruction(20 downto 16)) when RegOutport = '1' else  --OUTP
						conv_integer(Instruction(25 downto 21));
						
Read_register2 <= conv_integer(Instruction(20 downto 16));

Write_register <= conv_integer(Instruction(20 downto 16)) when RegImport = '1' else  --MUX INP
						conv_integer(Instruction(20 downto 16)) when RegDst = '0' else  --MUX
						conv_integer(Instruction(15 downto 11));
						
Write_data <=  x"0000"&Instruction(15 downto 0) when RegImport = '1' else  --INP
					ALUResult when MemtoReg = '0' else
					Read_mem_data;		
					
Output <= Read_data1 when RegOutport = '1' else  --OUTP
			 x"FFFFFFFF";			
						
Register_part:
Registers port map(clk,Reset,RegWrite,Read_register1,Read_register2,Write_register,
						 Write_data,Read_data1,Read_data2);


--ALU
ALU_B <= Read_data2 when ALUSrc = '0' else
			Extendout;

ALU_part:
ALU port map (Read_data1,ALU_B,Operation,ALUresult,Zero);


--Data Memory	

Data_mem:
Data_memory port map (clk,conv_integer(ALUResult(7 downto 2)),Read_data2,MemWrite,MemRead,Read_mem_data);

--Control	

Control_part:
Control port map (Instruction(31 downto 26),Jump,Halt,RegImport,RegOutport,RegDst,Branch,MemRead,MemtoReg,ALUOp,MemWrite,ALUSrc,RegWrite);									

--ALUControl	

ALUControl_part:
ALUControl port map (ALUOp,Instruction(5 downto 0),Operation);									


--Sign_extend	

Sign_extend_part:
Sign_extend port map (Instruction(15 downto 0),Extendout);


--Add_32bit	
Add_32bit_A <= PC + 4;
Add_32bit_B <= Extendout(29 downto 0) & "00"; 

Add_32bit_part:
Add_32bit port map (Add_32bit_A,Add_32bit_B,AddResult);

PCout <= PC(7 downto 0);
ALUout <= ALUResult;
Instout <= Instruction;
ALUopout <= Operation;
	
end MIPS;