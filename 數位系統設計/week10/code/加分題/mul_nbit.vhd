library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mul_nbit is
    generic(number:integer range 1 to 32 :=4);                                                      -- 改成可調整為數，方便列舉 1~12 階層
    port(
        clk : in std_logic;                                                                         -- 做乘法最多做 bits 次，所以要有時脈
        multiplier : in std_logic_vector(number-1 downto 0);                                        -- 輸入來源
        multiplicand : in std_logic_vector(number-1 downto 0);
        product : out std_logic_vector(2*number-1 downto 0)                                         -- 輸出結果
    );
end mul_nbit;

architecture mul8bit of mul_nbit is
    signal muland_reg : std_logic_vector(number-1 downto 0):=(multiplier);
    signal product_reg : std_logic_vector(2*number-1 downto 0):=(others => '0');
    signal cnt : std_logic_vector(number-1 downto 0):=(others => '0');                              -- 由於無法確定 bits 數，只要確保一個必定足夠的位數就好，這必定超除很多
begin
    process(clk)
        variable tmp : std_logic_vector(number downto 0):=(others => '0');                          -- 避免浪費時間回復狀態，使用暫存判斷(考慮進位)
    begin
        if clk'event and clk = '1' then
            if cnt < number then                                                                    -- 小於bits 數就繼續做
                if product_reg(0) = '1' then                                                        -- LSB 為1，左半相加後右移(考慮進位)
                    tmp := ('0' & product_reg(2*number-1 downto number)) + ('0' & muland_reg);
                    product_reg <= tmp & product_reg(number-1 downto 1);
                else
                    product_reg <= '0' & product_reg(2*number-1 downto 1);                          -- 直接又一補零
                end if;
                cnt <= cnt + 1;                                                                     -- 計算次數
            end if;
        end if;
    end process;

    product <= product_reg;                                                                          -- 輸出                                        
end mul8bit;
