library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity cascaded_BCD_cnt is
    port(
        clk:in std_logic;
        reset:in std_logic;
        casin:in std_logic;
        casout:out std_logic;
        Q:out std_logic_vector(3 downto 0)
    );
end cascaded_BCD_cnt;

architecture BCD_cnt of cascaded_BCD_cnt is
    signal cnt:std_logic_vector(3 downto 0);
begin
    process(clk, reset)
    begin
        if reset = '0' then
            cnt <= (others => '0');
        elsif rising_edge(clk) then
            if casin = '1' then
                if cnt < 9 then
                    cnt <= cnt + '1';
                else
                    cnt <= (others => '0');
                end if;
            end if;
        end if;
    end process;
    casout <= '1' when cnt ="1001" else
              '0';
    Q <= cnt;
end BCD_cnt;