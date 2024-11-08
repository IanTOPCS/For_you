library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity FA_nbit is
    generic(number:integer range 1 to 32 :=4);              -- 接受輸入 1~32 整數的數值當作 bits 數
    port(
        A:in std_logic_vector(number-1 downto 0);           -- 實現加法，套用輸入 bits 數，range 含 0，故 -1
        B:in std_logic_vector(number-1 downto 0);
        cin:in std_logic;                                   -- 考慮重複利用，接受外部進位
        Q:out std_logic_vector(number-1 downto 0);          -- 加法結果
        cout:out std_logic                                  -- 考慮重複利用，輸出內部進位
    );
end FA_nbit;

architecture Behavioral of FA_nbit is
    signal tmp:std_logic_vector(number downto 0);           -- MSB 為內部進位，故延伸 1 bit
begin
    tmp <= ('0' & A) + B + cin;                             -- 內部兩個來源+外部進位為所有輸出                
    Q <= tmp(number-1 downto 0);                            -- Q 不應該包含進位
    cout <= tmp(number);                                    -- 輸出進位
end Behavioral;