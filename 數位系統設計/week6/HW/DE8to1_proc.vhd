library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE8to1_proc is
    port(
        I:in std_logic_vector(7 downto 0);
        S:in std_logic_vector(2 downto 0);
        X:out std_logic
    );
    procedure DE2to1 (signal I:in std_logic_vector(1 downto 0); signal S:in std_logic; signal X:out std_logic) is
    begin
        if(S = '1') then                                    -- 依照規定，1 輸出下位
            X <= I(1);                                      -- 直接對內容更改，而非回傳
        elsif (S = '0') then                                -- 依照規定，0 輸出上位
            X <= I(0);
        end if;
    end DE2to1;
end DE8to1_proc;

architecture DE8to1_proc of DE8to1_proc is
    signal first_row:std_logic_vector(3 downto 0);          -- 一二層連接signal
    signal second_row:std_logic_vector(1 downto 0);         -- 二三層連接signal
begin
    DE2to1 (I(1 downto 0), S(2), first_row(0));             -- 第一層電路，不須接收return value，已經將輸出接至first_row
    DE2to1 (I(3 downto 2), S(2), first_row(1));
    DE2to1 (I(5 downto 4), S(2), first_row(2));
    DE2to1 (I(7 downto 6), S(2), first_row(3));

    DE2to1 (first_row(1 downto 0), S(1), second_row(0));    -- 第二層電路，不須接收return value，已經將輸出接至second_row
    DE2to1 (first_row(3 downto 2), S(1), second_row(1));

    DE2to1 (second_row(1 downto 0), S(0), X);               -- 第三層電路，接上輸出
end DE8to1_proc;