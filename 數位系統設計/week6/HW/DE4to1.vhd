library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE4to1 is
    port(
        I:in std_logic_vector(3 downto 0);                -- 四項輸入
        S:in std_logic_vector(1 downto 0);                -- 兩層電路需要兩個select
        X:out std_logic                                   -- 最後輸出
    );
end DE4to1;

architecture DE4to1 of DE4to1 is
    signal tmp:std_logic_vector(1 downto 0);              -- 連接兩層電路間的signal
    component DE2to1                                      -- 組成單元
        port(
            I:in std_logic_vector(1 downto 0);
            S:in std_logic;
            X:out std_logic
        );
    end component;
begin
    DE0:DE2to1 port map(I(1 downto 0), S(1), tmp(0));     -- 引用元件，輸出放進signal
    DE1:DE2to1 port map(I(3 downto 2), S(1), tmp(1));     -- 引用元件，輸出放進signal
    DE2:DE2to1 port map(tmp, S(0), X);                    -- 第二層電路，接上輸出
end DE4to1;