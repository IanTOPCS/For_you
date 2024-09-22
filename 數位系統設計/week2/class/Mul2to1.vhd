library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Mul2to1 is
    port(
        A, B:in std_logic_vector(3 downto 0);
        F:out std_logic_vector(3 downto 0);
        S:in std_logic
    );
end Mul2to1;

architecture DataFlow of Mul2to1 is

begin
    F <= A when S = '0' else
         B;
end DataFlow;