library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE8to1 is
    port(
        I:in std_logic_vector(7 downto 0);                                      -- 最左方八項輸出
        S:in std_logic_vector(2 downto 0);                                      -- 三層電路需要三個select
        X:out std_logic                                                         -- 最後輸出
    );
end DE8to1;

architecture DE8to1 of DE8to1 is
    signal first_row:std_logic_vector(3 downto 0);                              -- 一二層連接signal
    signal second_row:std_logic_vector(1 downto 0);                             -- 二三層連接signal
    component DE2to1                                                            -- 引用元件
        port(
            I:in std_logic_vector(1 downto 0);
            S:in std_logic;
            X:out std_logic
        );
    end component;
begin                                                                           -- 暴力不能解決問題，就是不夠暴力
    DE0:DE2to1 port map(I=>I(1 downto 0), S=>S(2), X=>first_row(0));            -- 第一層電路連接
    DE1:DE2to1 port map(I=>I(3 downto 2), S=>S(2), X=>first_row(1));
    DE2:DE2to1 port map(I=>I(5 downto 4), S=>S(2), X=>first_row(2));
    DE3:DE2to1 port map(I=>I(7 downto 6), S=>S(2), X=>first_row(3));

    DE4:DE2to1 port map(I=>first_row(1 downto 0), S=>S(1), X=>second_row(0));   -- 第二層電路連接
    DE5:DE2to1 port map(I=>first_row(3 downto 2), S=>S(1), X=>second_row(1));

    DE6:DE2to1 port map(second_row(1 downto 0), S(0), X);                       -- 第三層電路連接
end DE8to1;