library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity upBCD_4bits_six is
    port(
        clk:in std_logic;
        reset:in std_logic;
        stop_pos:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end upBCD_4bits_six;

architecture upBCD_4bits_six of upBCD_4bits_six is
    signal cnt:std_logic_vector(3 downto 0):=(others => '0');
    signal flag:std_logic:='0';
begin
    process(clk, reset)
    begin
        if(reset = '0') then
            cnt <= x"0";
            flag <= '0';
        elsif stop_pos = '0' then
            cnt <= cnt;
            flag <= flag;
        elsif rising_edge(clk) then
            if(cnt = x"5")then      -- 時鐘的十位數
                cnt <= x"0";
                flag <= '1';
            else
                cnt <= cnt + '1';
                flag <= '0';
            end if;
        end if;
    end process;
    Q <= cnt;
    process(cnt)
    begin
        if ((cnt = x"0") and (flag = '1')) then
            casout <= '1';
        else
            casout <= '0';
        end if;
    end process;
end upBCD_4bits_six;