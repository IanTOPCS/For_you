library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity div_watch is
	port(
			clk:in std_logic;
			XY:in std_logic_vector(9 downto 0);
			sw0:in std_logic;
			sw1:in std_logic;
			start:in std_logic;
            re, q:out std_logic_vector(9 downto 0)                              -- 餘數、商(拉出來看結果)
			);
end div_watch;

architecture MUL_ver1 of div_watch is
    signal cnt:std_logic_vector(3 downto 0);                                    -- 指撥開關最多10個，且除法做bits次，最多10次
    signal divisor, dividen:std_logic_vector(9 downto 0);                       -- 除數、被除數
    signal remainder:std_logic_vector(19 downto 0);                             -- 左(餘)右(商)
    signal flag:std_logic;
begin
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
    re <= remainder(19 downto 10);                                                  -- 回填餘數
    q <= remainder(9 downto 0);                                                     -- 回填商
end MUL_ver1;