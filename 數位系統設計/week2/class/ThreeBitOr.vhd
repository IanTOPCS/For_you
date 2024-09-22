library IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity ThreeBitOr is
    port(
        A, B, C:in std_logic;
        F:out std_logic
    );
end ThreeBitOr;

architecture ThreeBitOr of ThreeBitOr is
    signal ABC: std_logic_vector(2 downto 0);
begin
    ABC <= A & B & C;
    F <= '0' when ABC = "000" else
         '1';
end ThreeBitOr;