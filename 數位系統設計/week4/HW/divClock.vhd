library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity divClock is
    port(
        CLK:in std_logic;
        mode:in std_logic_vector(1 downto 0);
        clkout:out std_logic
    );
end divClock;

architecture divClock of divClock is
    signal cnt:std_logic_vector(2 downto 0);            --最多數到6，3 bits計數器
begin
    process(CLK)                                        --規定各區間計數器區間
    begin
        if rising_edge(CLK) then
            if mode="00" then
                if cnt>="010" then
                    cnt <= (others => '0');
                else
                    cnt <= cnt+'1';
                end if;
            elsif mode="01" then
                if cnt>="011" then
                    cnt <= (others => '0');
                else
                    cnt <= cnt+'1';
                end if;
            elsif mode="10" then
                if cnt>="100" then
                    cnt <= (others => '0');
                else
                    cnt <= cnt+'1';
                end if;
            elsif mode="11" then
                if cnt>="101" then
                    cnt <= (others => '0');
                else
                    cnt <= cnt+'1';
                end if;
            end if;
        end if;
    end process;

    process(mode, cnt)
    begin
        case mode is
            when "00" =>                            --觀察發現如果需要copy CLK，1與0的設定不能交換
                if cnt<1 then
                    clkout <= '1';
                elsif cnt>1 then
                    clkout <= '0';
                else 
                    clkout <= CLK;
                end if;
            when "01" =>                            --不需要複製CLK，偶數可整除2 
                if cnt<2 then
                    clkout <= '1';
                elsif cnt>=2 then
                    clkout <= '0';
                end if;
            when "10" =>
                if cnt<2 then
                    clkout <= '1';
                elsif cnt>2 then
                    clkout <= '0';
                else 
                    clkout <= CLK;
                end if;
            when others =>
                if cnt<3 then
                    clkout <= '1';
                elsif cnt>=3 then
                    clkout <= '0';
                end if;
        end case;
    end process;
end divClock ; -- divClock