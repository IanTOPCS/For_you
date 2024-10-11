library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter is
    port(
        CLK:in std_logic;
        mode:in std_logic_vector(1 downto 0);
        Q:out std_logic_vector(7 downto 0)
    );
end counter;

architecture counter of counter is
    signal cnt:std_logic_vector(3 downto 0);                     --計數器
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            if (mode="10" or mode="11") and (cnt=x"D") then     --只有當模式"10"和"11"會在D結束一個週期
                cnt <= (others => '0');
            else
                cnt <= cnt + '1';                               --除了歸零即計數器上數
            end if;
        end if;
    end process;

    process(CLK)
    begin
        if rising_edge(CLK) then                                --令A正緣才觸發
            if mode="00" then                                   --令模式"00"為波型Q輸出
                case cnt is
                    when x"0" => Q <= "00000001";
                    when x"1" => Q <= "00000010";
                    when x"2" => Q <= "00000100";
                    when x"3" => Q <= "00001000";
                    when x"4" => Q <= "00010000";
                    when x"5" => Q <= "00100000";
                    when x"6" => Q <= "01000000";
                    when x"7" => Q <= "10000000";
                    when x"8" => Q <= "00000001";
                    when x"9" => Q <= "00000010";
                    when x"A" => Q <= "00000100";
                    when x"B" => Q <= "00001000";
                    when x"C" => Q <= "00010000";
                    when x"D" => Q <= "00100000";
                    when x"E" => Q <= "01000000";
                    when others => Q <= "10000000";
                end case;
            elsif mode="01" then                                --令模式"01"為波型Q輸出
                case cnt is
                    when x"0" => Q <= "10000000";
                    when x"1" => Q <= "01000000";
                    when x"2" => Q <= "00100000";
                    when x"3" => Q <= "00010000";
                    when x"4" => Q <= "00001000";
                    when x"5" => Q <= "00000100";
                    when x"6" => Q <= "00000010";
                    when x"7" => Q <= "00000001";
                    when x"8" => Q <= "10000000";
                    when x"9" => Q <= "01000000";
                    when x"A" => Q <= "00100000";
                    when x"B" => Q <= "00010000";
                    when x"C" => Q <= "00001000";
                    when x"D" => Q <= "00000100";
                    when x"E" => Q <= "00000010";
                    when others => Q <= "00000001";
                end case;
            elsif (mode="10" or mode="11") then                 --令模式"10"和"11"為波型Q輸出
                case cnt is
                    when x"0" => Q <= "00000001";
                    when x"1" => Q <= "00000010";
                    when x"2" => Q <= "00000100";
                    when x"3" => Q <= "00001000";
                    when x"4" => Q <= "00010000";
                    when x"5" => Q <= "00100000";
                    when x"6" => Q <= "01000000";
                    when x"7" => Q <= "10000000";
                    when x"8" => Q <= "01000000";
                    when x"9" => Q <= "00100000";
                    when x"A" => Q <= "00010000";
                    when x"B" => Q <= "00001000";
                    when x"C" => Q <= "00000100";
                    when others => Q <= "00000010";
                end case;
            end if;
        end if;
    end process;
end counter ; -- counter