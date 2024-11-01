library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DE0_test is
    port(
        clk:in std_logic;
        reset:in std_logic;
        stop:in std_logic;
        cout:out std_login;
        HEX0:out std_logic_vector(6 downto 0);
        HEX1:out std_logic_vector(6 downto 0);
        HEX2:out std_logic_vector(6 downto 0);
        HEX3:out std_logic_vector(6 downto 0)
    );
end DE0_test;

architecture DE0_test of DE0_test is
    signal bcd0,bcd1,bcd2,bcd3:std_logic_vector(3 downto 0);
    signal div, c1, c2, c3:std_logic;
    component Div_100hv is
        port(
            clk:in std_logic;
            clk100hz:out std_logic
        );
    end component;
    component cascaded_BCD_cnt is
        port(
            clk:in std_logic;
            reset:in std_logic;
            casin:in std_logic;
            casout:out std_logic;
            Q:out std_logic_vector(3 downto 0)
        );
    end component;
    component decorder_7seg is
        port(
            BCD:in std_logic_vector(3 downto 0);
            HEX:out std_logic_vector(6 downto 0)
        );
    end component;
begin

    DIV:Div_100hv port map(clk, div);
    CAS0:cascaded_BCD_cnt port map(div, reset, stop, c1, bcd0);
    CAS1:cascaded_BCD_cnt port map(div, reset, c1, c2, bcd1);
    CAS2:cascaded_BCD_cnt port map(div, reset, c2, c3, bcd2);
    CAS3:cascaded_BCD_cnt port map(div, reset, c3, cout, bcd3);
    DEC0:decorder_7seg port map(bcd0, HEX0);
    DEC1:decorder_7seg port map(bcd1, HEX1);
    DEC2:decorder_7seg port map(bcd2, HEX2);
    DEC3:decorder_7seg port map(bcd3, HEX3);
end DE0_test;