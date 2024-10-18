library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE2to1 is
    port(
        I:in std_logic_vector(1 downto 0);           -- 此項作業的基本component，兩項輸入
        S:in std_logic;                              -- select 線，選擇高低位輸出
        X:out std_logic                              -- 選擇後的輸出
    ); 
end DE2to1;

architecture DE2to1 of DE2to1 is
begin
    process(S, I)                                    -- 偵測所有輸入、選擇線
    begin
        if(S = '0') then                             -- select 0 表示 選擇 I(0)
            X <= I(0);
        elsif(S = '1') then                          -- select 1 表示 選擇 I(1)
            X <= I(1);
        end if;
    end process;
end DE2to1;