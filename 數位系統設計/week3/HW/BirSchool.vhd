library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity BirSchool is
    port(
        CLK:in std_logic;
        ans:out std_logic_vector(2 downto 0);
        RESET:in std_logic
    );
end BirSchool;

architecture BirSchool of BirSchool is
    signal cnt:std_logic_vector(4 downto 0);
begin
    process(RESET, CLK)                                    --200401257027
    begin
        if RESET = '0' then
            cnt <= "00" & "010";                          --強制回到開頭
        elsif rising_edge(CLK) then
            case cnt is
                when "00" & "010" => cnt <= "00" & "000"; --2>0
                when "00" & "000" => cnt <= "01" & "000"; --0>0
                when "01" & "000" => cnt <= "00" & "100"; --0>4
                when "00" & "100" => cnt <= "10" & "000"; --4>0
                when "10" & "000" => cnt <= "00" & "001"; --0>1
                when "00" & "001" => cnt <= "01" & "010"; --1>2
                when "01" & "010" => cnt <= "00" & "101"; --2>5
                when "00" & "101" => cnt <= "00" & "111"; --5>7
                when "00" & "111" => cnt <= "11" & "000"; --7>0
                when "11" & "000" => cnt <= "10" & "010"; --0>2
                when "10" & "010" => cnt <= "01" & "111"; --2>7
                when "01" & "111" => cnt <= "00" & "010"; --7>2
                when others => cnt <= "00" & "010";       --強制回到開頭
            end case;
        end if;
    end process;
    ans <= cnt(2 downto 0);                              --更新結果
end BirSchool;