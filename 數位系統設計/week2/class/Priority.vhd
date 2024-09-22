library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Priority is
    port(
        A, B, C, X, Y:in std_logic;
        F:out std_logic
    );
end Priority;

architecture Priority of Priority is

begin
    F <= A when X = '1' else
         B when Y = '1' else
         C;
end Priority;