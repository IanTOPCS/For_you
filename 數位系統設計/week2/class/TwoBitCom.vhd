library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity TwoBitCom is
    port(
        A, B:in std_logic;
        LARGE, SMALL, EQV:out std_logic
    );
end TwoBitCom;

architecture DataFlow of TwoBitCom is

begin
    LARGE <= A and (not B);
    SMALL <= (not A) and B;
    EQV <= ((not A)and(not B))or(A and B);
end DataFlow;