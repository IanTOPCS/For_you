
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity MIPS is
	port(
			clk:in std_logic;
			SWin:in std_logic_vector(9 downto 0);
			Reset:in std_logic;
			PCout:out std_logic_vector(5 downto 0);
			DP:out std_logic_vector(3 downto 0);			
			Hex0,Hex1,Hex2,Hex3:out std_logic_vector(6 downto 0);
			OUTLED:out std_logic_vector(2 downto 0)
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
						Reset:in std_logic;				
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
						SWImport:out std_logic;							
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
						RegWrite:out std_logic;
						OUTLED:out std_logic
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
			
			component digits_large is
			port(
					BIN:in integer range 0 to 99999999;
					num7: out integer range 0 to 9;
					num6: out integer range 0 to 9;
					num5: out integer range 0 to 9;
					num4: out integer range 0 to 9;			
					num3: out integer range 0 to 9;
					num2: out integer range 0 to 9;
					num1: out integer range 0 to 9;
					num0: out integer range 0 to 9		
					);
					
			end component;

			component decoder_7seg is
				PORT(
						BCD:in std_logic_vector(3 downto 0);
						HEX:out std_logic_vector(6 downto 0)
						);
			end component;			
			
			
		type INT_array is Array (0 to 3) of integer range 0 to 9;
		type INT_array_large is Array (0 to 7) of integer range 0 to 9;		
		type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
		signal num1,num2: INT_array;	
		signal num: INT_array_large;	
		signal P:std_logic_vector(19 downto 0);	
		signal show:LOGIC_array;
		signal cnt:std_logic_vector(25 downto 0);			

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
		signal SWImport,Jump,Halt,RegImport,RegOutport:std_logic;
		signal Branch,RegDst,MemRead,MemtoReg,MemWrite,ALUSrc,RegWrite, OUTLEDsig:std_logic;
		signal ALUop:std_logic_vector(1 downto 0);

		signal Read_register1,Read_register2,Write_register:integer range 0 to 31;
		signal Write_data:std_logic_vector(31 downto 0);
		
		signal Add_32bit_A:std_logic_vector(31 downto 0);
		signal Add_32bit_B:std_logic_vector(31 downto 0);
		signal AddResult:std_logic_vector(31 downto 0);	
		signal Output:std_logic_vector(31 downto 0);
	
		signal delay:integer range 0 to 150000000;
		signal flag0, flag1, flag2:std_logic := '0';

begin
--Program Counter	
	process(clk,reset)
	begin
		if reset = '0' then
			PC <= (others => '0');
			delay <= 0;
			flag0 <= '1';
			OUTLED(0) <= '1';							-- 一開始亮最左一個LED
			OUTlED(1) <= '0';
			OUTLED(2) <= '0';
		elsif clk'event and clk = '1' then
			if Branch = '1' and Zero = '1' then
				PC <= AddResult;
 
			elsif Jump = '1' and flag2 = '1' and delay = 24999999 then --直到暫停的時間結束，PC指到下一個指令
			--elsif Jump = '1' and flag0 = '1' and delay = 1 then
			--else
				delay <= 0;							-- 歸零重新計算
				flag0 <= '1';						-- 最右不亮
				flag2 <= '0';						-- 最左亮起
				OUTLED(0) <= '1';					-- 開啟最左
				OUTLED(2) <= '0';					-- 關掉最右
				PC <= PC(31 downto 28)&Instruction(25 downto 0)&"00";				
			elsif Halt = '0' then
			--else
				delay <= delay + 1;					-- 延遲所有過程，讓PC暫停
			end if;
			
			if OUTLEDsig = '1' and flag0 = '1' and delay = 149999999 then	--直到暫停的時間結束，PC指到下一個指令
			--if OUTLEDsig = '1' and flag2 = '1' and delay = 11 then
				delay <= 0;
				OUTLED(0) <= '0';					-- 關掉最左
				OUTLED(1) <= '1';					-- 開啟中間
				flag0 <= '0';						-- 最左不亮
				flag1 <= '1';						-- 中間亮起
				PC <= PC +4;
			elsif OUTLEDsig = '1' and flag1 = '1' and delay = 149999999 then --直到暫停的時間結束，PC指到下一個指令
			--elsif OUTLEDsig = '1' and flag1 = '1' and delay = 11 then
				delay <= 0;
				OUTLED(1) <= '0';					-- 關掉中間
				OUTLED(2) <= '1';					-- 開啟最右
				flag1 <= '0';						-- 中間不亮
				flag2 <= '1';						-- 最右亮起
				PC <= PC +4;
			end if;
		end if;
	end process;	
	
--Instruction Memory	

Inst_Memory_part:
Instruction_memory port map (Reset,conv_integer(PC(7 downto 2)),Instruction);



--Registers	
Read_register1 <= conv_integer(Instruction(20 downto 16)) when RegOutport = '1' else
						conv_integer(Instruction(25 downto 21));
						
Read_register2 <= conv_integer(Instruction(20 downto 16));

Write_register <= conv_integer(Instruction(20 downto 16)) when RegImport = '1' else  --MUX
						conv_integer(Instruction(20 downto 16)) when SWImport = '1' else  --MUX SWIN
						conv_integer(Instruction(20 downto 16)) when RegDst = '0' else  --MUX
						conv_integer(Instruction(15 downto 11));
						
Write_data <=  x"0000"&Instruction(15 downto 0) when RegImport = '1' else
					x"0000"&"000000"&SWin when SWImport = '1' else   --"0000000000000000000000"
					ALUResult when MemtoReg = '0' else
					Read_mem_data;		

	
						
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
Control port map (Instruction(31 downto 26),SWImport,Jump,Halt,RegImport,RegOutport,RegDst,Branch,MemRead,MemtoReg,ALUOp,MemWrite,ALUSrc,RegWrite, OUTLEDsig);									

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

PCout <= PC(5 downto 0);


	
----------------------------------------------------------------------------
process(clk,Reset)			
begin
	if Reset = '0' then
		output <= x"00000000";
	elsif clk'event and clk = '0' then  --fall edge
		if RegOutport = '1' then
		  Output <= Read_data1;
		end if; 
	end if;
end process;	

---------------------------------------------------------------------------------------------------------

			process(clk) 
			begin
				if clk'event and clk = '1' then
					cnt <= cnt + 1;
				end if;
			end process;

		
U1:digits_large port map(Conv_integer(Output),num(7),num(6),num(5),num(4),num(3),num(2),num(1),num(0));	


show(0) <= conv_std_logic_vector(num(0),4)  when  cnt(25) = '0'  else
			  conv_std_logic_vector(num(4),4);  
			  
show(1) <= conv_std_logic_vector(num(1),4)  when  cnt(25) = '0' else
			  conv_std_logic_vector(num(5),4);

show(2) <= conv_std_logic_vector(num(2),4)  when  cnt(25) = '0'  else
			  conv_std_logic_vector(num(6),4);
			  
show(3) <= conv_std_logic_vector(num(3),4)  when  cnt(25) = '0'  else
			  conv_std_logic_vector(num(7),4);
			  

			  

HEX0_part:decoder_7seg port map(show(0),HEX0);  
HEX1_part:decoder_7seg port map(show(1),HEX1);
HEX2_part:decoder_7seg port map(show(2),HEX2);
HEX3_part:decoder_7seg port map(show(3),HEX3);		

DP<= "0000" when cnt(25) = '1' else
	  "1111";
	
end MIPS;