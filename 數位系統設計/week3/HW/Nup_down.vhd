library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Nup_down is
    port(
        up_clk:in std_logic;
        down_clk:in std_logic;
        RESET:in std_logic;
        ans:out std_logic_vector(3 downto 0)
    );
end Nup_down;

architecture Nup_down of Nup_down is
	signal cnt:std_logic_vector(3 downto 0);
   signal clk:std_logic;
begin
	clk <= (up_clk or down_clk);                    --當作唯一的clock
	process(clk, RESET)
	begin
		if RESET='0' then 
			cnt <= (others => '0');                 --重設
		elsif clk'event and clk='1' then            --正緣來時，當需要+1，down_clk必為0
			if down_clk='0' then
				cnt <= cnt+'1';
			else
				case cnt is                         --因為考慮到不只一個條件需要考慮，在未知情況下使用暴力枚舉
					when x"F" => cnt <= x"E";
					when x"E" => cnt <= x"D";
					when x"D" => cnt <= x"C";
					when x"C" => cnt <= x"B";
					when x"B" => cnt <= x"A";
					when x"A" => cnt <= x"9";
					when x"9" => cnt <= x"8";
					when x"8" => cnt <= x"7";
					when x"7" => cnt <= x"6";
					when x"6" => cnt <= x"5";
					when x"5" => cnt <= x"4";
					when x"4" => cnt <= x"3";
					when x"3" => cnt <= x"2";
					when x"2" => cnt <= x"1";
					when x"1" => cnt <= x"0";
					when x"0" => cnt <= x"F";
					when others => cnt <= X"0";     --只是為了符合文法
				end case;
			end if;
		end if;
	end process;
	ans <= cnt;                                     --輸出答案
end Nup_down;