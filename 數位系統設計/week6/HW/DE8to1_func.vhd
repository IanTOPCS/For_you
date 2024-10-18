library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE8to1_func is
    port(
        I:in std_logic_vector(7 downto 0);
        S:in std_logic_vector(2 downto 0);
        X:out std_logic
    );
    function DE2to1 (I:std_logic_vector(1 downto 0); S:std_logic) return std_logic is
    begin
        if(S = '1') then                                    -- 依照規定，1 輸出下位
            return I(1);                    
        elsif (S = '0') then                                -- 依照規定，0 輸出上位
            return I(0);
        else                                                -- 為滿足一定有return value
            return '0';
        end if;
    end DE2to1;
end DE8to1_func;

architecture DE8to1_func of DE8to1_func is
    signal first_row:std_logic_vector(3 downto 0);          -- 一二層連接signal
    signal second_row:std_logic_vector(1 downto 0);         -- 二三層連接signal
begin
    first_row(0) <= DE2to1(I(1 downto 0), S(2));            -- 將return value 以 function 方式得到並正確連接輸出
    first_row(1) <= DE2to1(I(3 downto 2), S(2));
    first_row(2) <= DE2to1(I(5 downto 4), S(2));
    first_row(3) <= DE2to1(I(7 downto 6), S(2));

    second_row(0) <= DE2to1(first_row(1 downto 0), S(1));   -- 第二層電路
    second_row(1) <= DE2to1(first_row(3 downto 2), S(1));

    X <= DE2to1(second_row(1 downto 0), S(0));              -- 第三層電路，接上輸出
end DE8to1_func;