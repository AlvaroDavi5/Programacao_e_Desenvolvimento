library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity main is
	port(
		sw : in  std_logic_vector(8 downto 0); -- 9 switches
		led : out std_logic_vector(4 downto 0) -- 5 LEDs
	);
end main;


architecture arch of main is
	signal n1, n2, n2_comp, n2_res : std_logic_vector(3 downto 0);
	signal res : std_logic_vector(4 downto 0);
	signal carry : std_logic_vector(3 downto 0);
begin

    n1 <= sw(3 downto 0);
    n2 <= sw(7 downto 4);

    n2_comp <= not n2;
	mux : entity work.mux(arch)
		port map(
			b0 => n2,
			b1 => n2_comp,
			op => sw(8),
			b_res => n2_res
		);

	op0 : entity work.full_adder(arch)
		port map(
			a => n1(0),
			b => n2_res(0),
			ci => sw(8),
			s => res(0),
			co => carry(0)
		);

	op1 : entity work.full_adder(arch)
		port map(
			a => n1(1),
			b => n2_res(1),
			ci => carry(0),
			s => res(1),
			co => carry(1)
		);

	op2 : entity work.full_adder(arch)
		port map(
			a => n1(2),
			b => n2_res(2),
			ci => carry(1),
			s => res(2),
			co => carry(2)
		);

	op3 : entity work.full_adder(arch)
		port map(
			a => n1(3),
			b => n2_res(3),
			ci => carry(2),
			s => res(3),
			co => carry(3)
		);

    led(0) <= res(0); 
    led(1) <= res(1); 
    led(2) <= res(2); 
    led(3) <= res(3); 
    led(4) <= carry(3);

end arch;

