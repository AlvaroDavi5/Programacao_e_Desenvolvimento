library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity debounce is
	port(
		clk   : in  std_logic;
		reset : in std_logic;
		btn   : in  std_logic;
		db    : out std_logic
	);
end debounce;

architecture arch of debounce is
	constant N    : integer := 22; -- (2^22)*10 ns (10 ms)
	signal q_reg  : unsigned(N - 1 downto 0);
	signal q_next : unsigned(N - 1 downto 0);
	signal button : std_logic;
begin
	-- counter
	process(clk, reset)
	begin
		if reset = '1' or q_reg > N then
			q_reg <= (others => '0');
		elsif (clk'event and clk = '1') then
			if btn /= button and q_reg = 0 then
				db <= btn;
				q_reg <= q_next;
			end if;
			button <= btn;
		end if;
	end process;
	-- next-state logic for the counter
	q_next <= q_reg + 1;

end arch;
