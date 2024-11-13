library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity mul_nbit_nohex is
	PORT(
			X:in std_logic_vector(3 downto 0);
			Y:in std_logic_vector(3 downto 0);
			sw:in std_logic_vector(1 downto 0);
			bt, bt2:in std_logic;
            show_ans:out std_logic_vector(15 downto 0);
            ans:out std_logic_vector(7 downto 0)
			);
end mul_nbit_nohex;

architecture mul_nbit_hex of mul_nbit_nohex is

		component mul_nn is
			generic(number :integer range 1 to 32);  
			PORT(
					X:in std_logic_vector(number-1 downto 0);
					Y:in std_logic_vector(number-1 downto 0);
					Ans:out std_logic_vector(2*number-1 downto 0)
					);
		end component;
		
		component digits is
		port(
				BIN:in integer range 0 to 9999;
				num3: out integer range 0 to 9;
				num2: out integer range 0 to 9;
				num1: out integer range 0 to 9;
				num0: out integer range 0 to 9		
				);
				
		end component;

		component add is
			port(
				X:in std_logic_vector(3 downto 0);
				Y:in std_logic_vector(3 downto 0);
				Q:out std_logic_vector(7 downto 0)
			);
		end component;
		
		component decoder_7seg is
			PORT(
					BCD:in std_logic_vector(3 downto 0);
					HEX:out std_logic_vector(6 downto 0)
					);
		end component;		
		

		type INT_array is Array (0 to 3) of integer range 0 to 9;
		type LOGIC_array is Array (0 to 3) of std_logic_vector(3 downto 0);		
		signal num,num1,num2: INT_array;		
		signal P, f0, f1, f2, f3:std_logic_vector(7 downto 0);
		signal f4:std_logic_vector(15 downto 0);	
		signal show:LOGIC_array;

begin

	FUN0: add port map(X, Y, f0);
    FUN1: mul_nn generic map(4) port map(X, Y, f1);
	FUN2: mul_nn generic map(4) port map(X, X, f2);
	FUN3: mul_nn generic map(4) port map(Y, Y, f3);
	FUN4: mul_nn generic map(8) port map(f2, f3, f4);

	process(sw, bt2)
	begin
		if (bt2 = '0') then
			p <= f4(7 downto 0);
		else 
			if (sw = "00") then
				p <= f0;
			elsif (sw = "01") then
				p <= f1;
			elsif (sw = "10") then
				p <= f2;
			elsif (sw = "11") then
				p <= f3;
			end if;
		end if;
	end process;
    ans <= p;

    U2:digits port map(Conv_integer(P),num(3),num(2),num(1),num(0));

	U3:digits port map(Conv_integer(X),num1(3),num1(2),num1(1),num1(0));	
	U4:digits port map(Conv_integer(Y),num2(3),num2(2),num2(1),num2(0));	

	show(0) <= conv_std_logic_vector(num(0),4) when (bt = '0')or(bt2 = '0') else	
			conv_std_logic_vector(num1(0),4);
					
	show(1) <= conv_std_logic_vector(num(1),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num1(1),4);
				
	show(2) <= conv_std_logic_vector(num(2),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num2(0),4);

	show(3) <= conv_std_logic_vector(num(3),4) when (bt = '0')or(bt2 = '0') else
			conv_std_logic_vector(num2(1),4);		
    show_ans <= show(3) & show(2) & show(1) & show(0);                          -- 為了可以顯示，將.vwf 時間壓在 1us，無法顯示出全部結果(最小的週期要取道0.多)故顯示部分以表正常運作
end mul_nbit_hex;