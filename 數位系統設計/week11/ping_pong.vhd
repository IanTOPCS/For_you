library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity ping_pong is
    port(
        clk:in std_logic;
        reset:in std_logic;
        A:in std_logic;
        B:in std_logic;
        led:out std_logic_vector(9 downto 0);
        HEX0, HEX1, HEX2, HEX3:out std_logic_vector(6 downto 0)
        );
end ping_pong;

architecture ping_pong of ping_pong is

    component decoder_7seg is
        PORT(
            BCD:in std_logic_vector(3 downto 0);
            HEX:out std_logic_vector(6 downto 0)
        );
    end component;

    component digits is
    port(
            BIN:in integer range 0 to 9999;
            num1: out integer range 0 to 9;
            num0: out integer range 0 to 9		
            );
    end component;

    type state is(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23, s24, s25, s26);
    signal present_state:state;
    signal next_state:state;
    signal dcnt:std_logic_vector(24 downto 0):=(others => '0');                 -- 2Hz 計數器
    signal clk2hz:std_logic;                                                    -- 輸出 2Hz
    signal Apoint, Bpoint:std_logic_vector(3 downto 0):="0000"; 
    signal flag:std_logic:='1'; 
    signal Aplus, Bplus:std_logic:='0';                                                -- 只有一次進到 s22                                       

    type INT_array is Array (0 to 3) of integer range 0 to 9;
    signal Anum, Bnum:INT_array;
    
    type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);
    signal show:LOGIC_array;
begin
    process(clk)
	begin
		if clk'event and clk = '1' then
			if dcnt = 24999999 then
				dcnt <= (others => '0');
			else
				dcnt <= dcnt + 1;
			end if;
		end if;
	end process;

	clk2hz <= dcnt(24);  --2Hz

    process(clk2hz,reset)
	begin
        if reset = '0' then 
            present_state <= s0;
        elsif rising_edge(clk2hz) then
            present_state <= next_state;
        end if;
	end process;

    process(Aplus,reset)
	begin
		if reset = '0' or present_state = s0 then
			Apoint <= "0000";
		elsif Aplus'event and Aplus = '1' then
			if Apoint < 11 then
				Apoint <= Apoint + 1;
			end if;
		end if;
	end process;

    process(Bplus,reset)
	begin
		if reset = '0' or present_state = s0 then
			Bpoint <= "0000";
		elsif Bplus'event and Bplus = '1' then
			if Bpoint < 11 then
				Bpoint <= Bpoint + 1;
			end if;
		end if;
	end process;

    process(present_state, A, B, Apoint, Bpoint, flag)
    begin
        case present_state is
            when s0 => 
                if (A = '0') then 
                    next_state <= s1;
                else
                    next_state <= s0;
                end if;
                led <= (others => '0');
                Apoint <= "0000";
                Bpoint <= "0000";
                flag <= '1';
            when s1 =>
                next_state <= s2;
                led <= "1000000000";
            when s2 =>
                next_state <= s3;
                led <= "0100000000";
            when s3 =>
                next_state <= s4;
                led <= "0010000000";
            when s4 =>
                next_state <= s5;
                led <= "0001000000";
            when s5 =>
                next_state <= s6;
                led <= "0000100000";
            when s6 =>
                next_state <= s7;
                led <= "0000010000";
            when s7 =>
                next_state <= s8;
                led <= "0000001000";                
            when s8 =>
                next_state <= s9;
                led <= "0000000100";
            when s9 =>
                if(B = '0')then
                    next_state <= s20;
                    Apoint <= Apoint + '1';
                else
                    next_state <= s10;
                end if;
                led <= "0000000010";
            when s10 =>
                if(B = '0') then
                    next_state <= s11;
                else
                    next_state <= s20;
                    Apoint <= Apoint + '1';
                end if;
                led <= "0000000001";
            when s20 =>
                if(B = '0')then
                    next_state <= s21;
                else
                    next_state <= s20;
                end if;
                led <= (others => '0');
            when s21 =>
                next_state <= s11;
                led <= "0000000001";
            when s11 =>
                next_state <= s12;
                led <= "0000000010";
            when s12 =>
                next_state <= s13;
                led <= "0000000100";
            when s13 =>
                next_state <= s14;
                led <= "0000001000";
            when s14 => 
                next_state <= s15;
                led <= "0000010000";
            when s15 =>
                next_state <= s16;
                led <= "0000100000";
            when s16 =>
                next_state <= s17;
                led <= "0001000000";
            when s17 =>
                next_state <= s18;
                led <= "0010000000";
            when s18 =>
                if(A = '0')then
                    next_state <= s0;
                    Bpoint <= Bpoint + '1';
                else
                    next_state <= s19;
                end if;
                led <= "0100000000";
            when s19 =>
                if(A = '0')then
                    next_state <= s2;
                else
                    next_state <= s0;
                    Bpoint <= Bpoint + '1';
                end if;
                led <= "1000000000";
            when s22 =>
                next_state <= s23;
                led <= (others => '1');
            when s23 =>
                next_state <= s24;
                led <= (others => '0');
            when s24 =>
                next_state <= s25;
                led <= (others => '1');
            when s25 =>
                next_state <= s26;
                led <= (others => '0');
            when s26 =>
                next_state <= s0;
                led <= (others => '1');
        end case;
        if(((Apoint = "1011") or (Bpoint = "1011")) and (flag = '1'))then
            next_state <= s22;
            flag <= '0';
        end if;
    end process;

    U0:digits port map(conv_integer(Apoint), Anum(1), Anum(0));
    U1:digits port map(conv_integer(Bpoint), Bnum(1), Bnum(0));
    show(0) <= conv_std_logic_vector(Anum(0), 4);
    show(1) <= conv_std_logic_vector(Anum(1), 4);
    show(2) <= conv_std_logic_vector(Bnum(0), 4);
    show(3) <= conv_std_logic_vector(Bnum(1), 4);
    HEX0_part:decoder_7seg port map(show(0), HEX0);
    HEX1_part:decoder_7seg port map(show(1), HEX1);
    HEX2_part:decoder_7seg port map(show(2), HEX2);
    HEX3_part:decoder_7seg port map(show(3), HEX3);
    
end ping_pong;