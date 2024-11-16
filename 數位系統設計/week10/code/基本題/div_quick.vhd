library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity div_quick is
	port(
			clk:in std_logic;
			XY:in std_logic_vector(9 downto 0);
			sw0:in std_logic;
			sw1:in std_logic;
			start:in std_logic;
            dp:out std_logic_vector(3 downto 0);                                -- 接出來看看是否在餘數時顯示 
			HEX0,HEX1,HEX2,HEX3:out std_logic_vector(6 downto 0)
			);
end div_quick;
architecture MUL_ver1 of div_quick is
        component digits is
        port(
                BIN:in integer range 0 to 9999;
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
    signal cnt:std_logic_vector(3 downto 0);                                    -- 指撥開關最多10個，且除法做bits次，最多10次
    signal cnt1:std_logic_vector(25 downto 0);                                  -- 除頻器
    signal divisor, dividen:std_logic_vector(9 downto 0);                       -- 除數、被除數
    signal remainder:std_logic_vector(19 downto 0);                             -- 左(餘)右(商)
    type INT_array is Array (0 to 3) of integer range 0 to 9;
    type INT_array_large is Array (0 to 7) of integer range 0 to 9;		
    type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
    signal divisor_num, dividen_num: INT_array;	                                -- 除數、被除數
    signal remainder_num: INT_array_large;	                                    -- 餘數、商
    signal show:LOGIC_array;
    signal flag:std_logic;
begin
	process(clk)
	begin
		if clk'event and clk = '1' then
			cnt1 <= cnt1 + 1;
		end if;
	end process;
	process(sw0)                                                                    -- 被除數
	begin
		if sw0 = '0' then
			dividen <= XY;
		end if;
	end process;
	process(sw0,start)
	begin
		if sw0 = '0' and start = '1' then
			flag <= '0';
		elsif sw0 = '1' and start = '0' then	
			flag <= '1';
		end if;
	end process;	
	process(sw1)                                                                    -- 除數
	begin
		if sw1 = '0' then
            divisor <= XY;
		end if;
	end process;
	process(clk,start)
	variable remainder_reg:std_logic_vector(19 downto 0);
	variable divisor_reg, tmp:std_logic_vector(9 downto 0);	
	begin
		if start = '0' then
			tmp := (others => '0');
            divisor_reg := divisor;
            remainder_reg := ("000000000" & dividen & '0');
			cnt <= "0000";
		elsif (rising_edge(clk)) then
			if cnt < 10 then
                cnt <= cnt + 1;
                tmp := remainder_reg(19 downto 10) - divisor_reg;
                if(tmp(9) = '0') then
                    remainder_reg := tmp(8 downto 0) & remainder_reg(9 downto 0) & '1';
                else
                    remainder_reg := remainder_reg(18 downto 0) & '0';    
                end if;
			elsif (cnt = 10) then
                cnt <= cnt +1;
                remainder_reg := '0' & remainder_reg(19 downto 11) & remainder_reg(9 downto 0);
			end if;
		end if;	
        remainder <= remainder_reg;
	end process;	
    U0:digits port map(Conv_integer(remainder(19 downto 10)),remainder_num(7),remainder_num(6),remainder_num(5),remainder_num(4));	
    U1:digits port map(Conv_integer(remainder(9 downto 0)),remainder_num(3),remainder_num(2),remainder_num(1),remainder_num(0));
    U2:digits port map(Conv_integer(dividen),dividen_num(3),dividen_num(2),dividen_num(1),dividen_num(0));	
    U3:digits port map(Conv_integer(divisor),divisor_num(3),divisor_num(2),divisor_num(1),divisor_num(0));	
    show(0) <= conv_std_logic_vector(dividen_num(0),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(0),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(0),4)  when clk = '0' and flag = '1' else                                   -- 改掉除頻器
                conv_std_logic_vector(remainder_num(4),4) when clk = '1' and flag = '1' else                                -- 改掉除頻器
                "1111";             
    show(1) <= conv_std_logic_vector(dividen_num(1),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(1),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(1),4)  when clk = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(5),4)  when clk = '1' and flag = '1' else
                "1111";
    show(2) <= conv_std_logic_vector(dividen_num(2),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(2),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(2),4)  when clk = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(6),4)  when clk = '1' and flag = '1' else  
                "1111";
    show(3) <= conv_std_logic_vector(dividen_num(3),4) when sw0 = '0' else
                conv_std_logic_vector(divisor_num(3),4) when sw1 = '0' else	
            conv_std_logic_vector(remainder_num(3),4)  when clk = '0' and flag = '1' else
                conv_std_logic_vector(remainder_num(7),4)  when clk = '1' and flag = '1' else
                "1111";			                  
    dp <= (others => '0') when (flag = '1' and clk = '1') else (others => '1');                                             -- 改掉除頻器
    HEX0_part:decoder_7seg port map(show(0),HEX0);  
    HEX1_part:decoder_7seg port map(show(1),HEX1);
    HEX2_part:decoder_7seg port map(show(2),HEX2);
    HEX3_part:decoder_7seg port map(show(3),HEX3);			
end MUL_ver1;			