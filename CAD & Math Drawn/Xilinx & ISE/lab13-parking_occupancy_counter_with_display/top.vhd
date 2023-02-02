-- TODO: testar display
library ieee;
use ieee.std_logic_1164.all;


entity top is
	port (
		clk  : in std_logic;
		btn  : in std_logic_vector(2 downto 0);
		led  : out std_logic_vector(0 downto 0);
		an   : out std_logic_vector(3 downto 0);
		sseg : out std_logic_vector(7 downto 0)
	);
end top;

architecture arch of top is
	constant N : integer := 99999999;
	signal enable : std_logic;
	signal divide_clk : integer range 0 to N;
	signal inc, dec, max_tick : std_logic;
	signal btn0, btn1, reset_btn : std_logic;
	signal result : std_logic_vector(3 downto 0);
begin
	-- clock division
	process (clk) begin
		if (clk'event and clk = '1') then
			divide_clk <= divide_clk + 1;
			if divide_clk = N then
				divide_clk <= 0;
			end if;
		end if;
	end process;
	enable <= '1' when divide_clk = N else '0';

	reset_btn = btn(0);

	-- debouncing
	db0: entity work.debounce
	port map(
		btn => btn(1),
		db => btn0,
		clk => clk,
		reset => reset_btn
	);
	db1: entity work.debounce
	port map(
		btn => btn(2),
		db => btn1,
		clk => clk,
		reset => reset_btn
	);

	-- finite state machine
	fsm: entity work.fsm
	port map(
		a => btn0,
		b => btn1,
		car_enter => inc,
		car_exit => dec,
		clk => clk,
		reset => reset_btn,
		enable => enable
	);

	-- parking register
	register: entity work.register
	port map(
		clk => clk,
		reset => reset_btn,   
		enable => enable,   
		inc => inc,
		dec => dec,
		q => result,
		max_tick => max_tick
	);

	-- display
	display_mux: entity work.disp_hex_mux
	port map(
		clk => clk,
		reset => reset_btn,   
		hex0 => result,
		hex1 => result,
		hex2 => result,
		hex3 => result,
		an => an,
		sseg => sseg
	);

	led(0) <= max_tick;
end arch;
