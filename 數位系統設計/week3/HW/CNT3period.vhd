library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity CNT3period is
    port(
        CLK:in std_logic;
        RESET:in std_logic;
        S:in std_logic_vector(1 downto 0);
        ans:out std_logic_vector(4 downto 0)
    );
end CNT3period;

architecture CNT3period of CNT3period is
    signal cnt:std_logic_vector(4 downto 0);
begin
    process(CLK, RESET)
    begin
        if RESET='0' then                           --重置當下計數器
            if S="00" then
                cnt <= "01010";
            elsif S="01" then
                cnt <= "10100";
            elsif (S="10" or S="11") then
                cnt <= "00010";
            end if;
        elsif CLK'event and CLK='1' then            --正緣觸發
            if S="00" then                          --"00"為10~30上數1
                if cnt>="11110" then                --大於等於30變成10
                    cnt <= "01010";
                elsif cnt<"01001" then              --小於10變成10
                    cnt <= "01010";
                else
                    cnt <= cnt+"00001";
                end if;
            elsif S="01" then                       --"01"為20~5下數1
                if cnt<="00101" then                --小於等於5變成20
                    cnt <= "10100";
                elsif cnt>"10100" then              --大於20變成20
                        cnt <= "10100";
                else
                    cnt <= cnt-"00001";
                end if;
            elsif (S="10" or S="11") then           --"10"和"11"為2~28上數2
                if cnt>="11011" then                --大於等於27變成2
                    cnt <= "00010";
                elsif cnt<"00010" then              --小於2變成2
                    cnt <= "01010";
                else
                    cnt <= cnt+"00010";
                end if;
            end if;
        end if;
    end process;
    ans <= cnt;
end CNT3period;