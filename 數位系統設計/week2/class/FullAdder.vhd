library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity FullAdder is
    port(
        c0:in std_logic;
        x0:in std_logic;
        y0:in std_logic;
        c1:out std_logic;
        s0:out std_logic
    );
end  FullAdder;

architecture FullAdder of FullAdder is

begin
    s0 <= x0 xor c0 xor y0;
    c1 <= (x0 and y0)or(y0 and c0)or(x0 and c0);
end FullAdder;