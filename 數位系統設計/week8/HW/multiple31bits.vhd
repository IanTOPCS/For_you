library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiple31bits is
    port(
        X:in std_logic_vector(4 downto 0):=(others => '0');         -- 接 component 接口
        Y:in std_logic_vector(4 downto 0):=(others => '0');
        Ans:out std_logic_vector(9 downto 0):=(others => '0')
    );
end multiple31bits;

architecture Behavioral of multiple31bits is
    component mul_nn is
        generic(number:integer range 1 to 32);
        port(
            X:in std_logic_vector(number-1 downto 0);
            Y:in std_logic_vector(number-1 downto 0);
            Ans:out std_logic_vector(2*number-1 downto 0)
        );
    end component;
begin
    fun0:mul_nn generic map(5) port map(X, Y, Ans);                 -- 寫此 code 的目的，令 generic number 為 5，符合題意
end Behavioral;