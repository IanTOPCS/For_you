library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity mul_nn is
    generic(number:integer range 1 to 32 :=4);
    port(
        X:in std_logic_vector(number-1 downto 0);                                                                                                               -- n bis 數字 range = ((n-1)~0) 
        Y:in std_logic_vector(number-1 downto 0);
        Ans:out std_logic_vector(2*number-1 downto 0):=(others => '0')                                                                                          -- n bits 乘法結果最多 2n bits, range = ((2n-1)~0)
    );
end mul_nn;

architecture Behavioral of mul_nn is
    type MulEhRow is array(0 to number-1) of std_logic_vector(number-1 downto 0);                                                                               -- 假設 X 在上 Y 在下，Y 每個 bit 與 X 相乘的結果存放於此。n bits * n bits 最多 n 列
    type AdTmp is array(0 to number-2) of std_logic_vector(number downto 0);                                                                                    -- 將乘完結果相加，需做 (n-1) 次
    signal mulEachRow : MulEhRow := (others => (others => '0'));
    signal addTmp : AdTmp := (others => (others => '0'));
    signal tmp:std_logic_vector(number-1 downto 0);                                                                                                             -- 為了 modelsim 正常運作，因為不接受參數進行額外運算，故使用暫存方式將結果當作固定值丟入function
    component FA_nbit is
        generic(number:integer range 1 to 32);
        port(
            A:in std_logic_vector(number-1 downto 0);
            B:in std_logic_vector(number-1 downto 0);
            cin:in std_logic;
            Q:out std_logic_vector(number-1 downto 0);
            cout:out std_logic
        );
    end component;
begin
    process(X, Y)                                                                                                                                               -- X 與 Y 相乘，故偵測兩者
    begin
        for i in 0 to (number-1) loop
            for j in 0 to (number-1) loop
                mulEachRow(i)(j) <= X(j) and Y(i);                                                                                                              -- 固定 i 取 j 每項乘法結果（假設 X 在上 Y 在下）                                                                                                                                                                                                                                             
            end loop;
        end loop;
    end process;

    LOP:for i in 0 to number-2 generate
    FIRST:  if i = 0 generate
                tmp <= ('0' & mulEachRow(i)(number-1 downto 1));
                FA:FA_nbit generic map(number) port map(tmp, mulEachRow(i+1), '0', addTmp(i)(number-1 downto 0), addTmp(i)(number));                            -- 當第一次相加，根據乘法，第一列MSB比第二列少 1 bit，考慮對齊，補0，並取相同 bits，LSB 應直接為答案 LSB
            end generate FIRST;
    MID:    if (i > 0) and (i < number-1) generate
                FA0:FA_nbit generic map(number) port map(addTmp(i-1)(number downto 1), mulEachRow(i+1), '0', addTmp(i)(number-1 downto 0), addTmp(i)(number));   -- 第一個來源已考慮進位，故外部進位0
            end generate MID;
    LAST:   if i = number-2 generate
                FA1:FA_nbit generic map(number) port map(addTmp(i-1)(number downto 1), mulEachRow(i+1), '0', Ans(2*number-2 downto number-1), Ans(2*number-1));  -- 最後一次相加結果應為答案相對應位置的 bits
            end generate LAST;
    end generate LOP;

    Ans(0) <= mulEachRow(0)(0);                                                                                                                                 -- 第一次相乘結果，LSB 即為答案 LSB

    process(addTmp)
    begin
        for i in 1 to (number-2) loop                                                                                                                           -- 相對位置剩下((number-2)~1)沒填 
            Ans(i) <= addTmp(i-1)(0);                                                                                                                           -- 將每列相乘結果 LSB 填入相對位置
        end loop;
    end process;

end Behavioral;