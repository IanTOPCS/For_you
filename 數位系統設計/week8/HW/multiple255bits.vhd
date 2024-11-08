library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity multiple255bits is
    port(
        X:in std_logic_vector(7 downto 0):=(others => '0');                    -- 接 component 接口
        Y:in std_logic_vector(7 downto 0):=(others => '0');
        Ans:out std_logic_vector(15 downto 0):=(others => '0')
    );
end multiple255bits;

architecture Behavioral of multiple255bits is
    component mul_nn is
        generic(number:integer range 1 to 32);
        port(
            X:in std_logic_vector(number-1 downto 0);
            Y:in std_logic_vector(number-1 downto 0);
            Ans:out std_logic_vector(2*number-1 downto 0)
        );
    end component;
begin
    fun0:mul_nn generic map(8) port map(X, Y, Ans);                             -- 寫此 code 的目的，令 generic number 為 8，符合題意(2^8 = 256, 為0~255)
end Behavioral;