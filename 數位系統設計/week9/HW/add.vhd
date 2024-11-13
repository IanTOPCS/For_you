library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity add is
    port(
        X:in std_logic_vector(3 downto 0);
        Y:in std_logic_vector(3 downto 0);
        Q:out std_logic_vector(7 downto 0)
    );
end add;

architecture add of add is
begin
    Q <= ("0000" & X) + ("0000" & Y);       -- 兩來源相加，補上正確位數的零以符合結果
end add;