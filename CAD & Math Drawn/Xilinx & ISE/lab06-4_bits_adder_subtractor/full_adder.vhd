library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity full_adder is
	port(
		a, b, ci : in  std_logic;
		s, co : out std_logic
	);
end full_adder;


architecture arch of full_adder is
    signal result, carry_out : std_logic;
begin

	adder : entity work.adder(arch)
            port map(
                num_a => a,
                num_b => b,
                res => result,
                co => carry_out
        );

    co <= carry_out or (result and not ci);
    s <= result xor not ci;

end arch;

