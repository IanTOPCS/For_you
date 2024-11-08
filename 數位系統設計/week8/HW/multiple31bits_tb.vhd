library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiple31bits_tb is
end multiple31bits_tb;

architecture Behavioral of multiple31bits_tb is
    component multiple31bits is
        port(
            X:in std_logic_vector(4 downto 0);
            Y:in std_logic_vector(4 downto 0);
            Ans:out std_logic_vector(9 downto 0)
        );
    end component;
    signal X, Y:std_logic_vector(4 downto 0):=(others => '0');
    signal Ans:std_logic_vector(9 downto 0):=(others => '0');
begin
    fun0:multiple31bits port map(X, Y, Ans);
    process
    begin
        for i in 0 to 31 loop
            X <= conv_std_logic_vector(i, 5);                       -- i 為 0~31 整數，轉成 std_logic_vector
            wait for 10 ns;                                         -- 等待 10 ns，轉換下一個狀態
        end loop;
    end process;

    process
    begin
        for i in 0 to 31 loop
            Y <= conv_std_logic_vector(i, 5); 
            wait for 5 ns;                                          -- 等待 5 ns，轉換下一個狀態，錯開以看到更多結果
        end loop;
    end process;
end Behavioral;