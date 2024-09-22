library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Decoder2to4_enComDecoder4tow16_en is
    port(
        I:in std_logic_vector(3 downto 0);
        en:in std_logic;
        Y:out std_logic_vector(15 downto 0)
    );
end Decoder2to4_enComDecoder4tow16_en;

architecture Dataflow of Decoder2to4_enComDecoder4tow16_en is
    signal Decoder2to4_en_out:std_logic_vector(3 downto 0);
begin
    Decoder2to4_en_out <= "1111" when en = '1' else
                          "1110" when I(3 downto 2) = "00" else
                          "1101" when I(3 downto 2) = "01" else
                          "1011" when I(3 downto 2) = "10" else
                          "0111" when I(3 downto 2) = "11";

    Y(3 downto 0) <= "0000" when Decoder2to4_en_out(0) = '1' else
                     "0001" when I(1 downto 0) = "00" else
                     "0010" when I(1 downto 0) = "01" else
                     "0100" when I(1 downto 0) = "10" else
                     "1000" when I(1 downto 0) = "11";

    Y(7 downto 4) <= "0000" when Decoder2to4_en_out(1) = '1' else
                     "0001" when I(1 downto 0) = "00" else
                     "0010" when I(1 downto 0) = "01" else
                     "0100" when I(1 downto 0) = "10" else
                     "1000" when I(1 downto 0) = "11";
                    
    Y(11 downto 8) <= "0000" when Decoder2to4_en_out(2) = '1' else
                      "0001" when I(1 downto 0) = "00" else
                      "0010" when I(1 downto 0) = "01" else
                      "0100" when I(1 downto 0) = "10" else
                      "1000" when I(1 downto 0) = "11";

     Y(15 downto 12) <= "0000" when Decoder2to4_en_out(3) = '1' else
                        "0001" when I(1 downto 0) = "00" else
                        "0010" when I(1 downto 0) = "01" else
                        "0100" when I(1 downto 0) = "10" else
                        "1000" when I(1 downto 0) = "11";
end Dataflow;