library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity decoder_7seg is
	PORT(
			BCD:in std_logic_vector(3 downto 0);
			HEX:out std_logic_vector(6 downto 0)
			);
end decoder_7seg;

architecture decoder_7seg of decoder_7seg is
begin

	HEX <=	"1000000" when BCD = 0 else
			"1111001" when BCD = 1 else
			"0100100" when BCD = 2 else
			"0110000" when BCD = 3 else
			"0011001" when BCD = 4 else
			"0010010" when BCD = 5 else
			"0000010" when BCD = 6 else
			"1111000" when BCD = 7 else
			"0000000" when BCD = 8 else
			"0010000" when BCD = 9 else
			"1111111";
end decoder_7seg;			