library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity top is
	port (
		sw : in std_logic_vector(1 downto 0);
		clk : in std_logic;
		an : out std_logic_vector(7 downto 0);
		sseg : out std_logic_vector(7 downto 0)
	);
end top;

architecture arch of top is
	constant N : integer := 99999999;
	signal enable : std_logic;
	signal inc, dec : std_logic;
	signal res : std_logic_vector(3 downto 0);
	signal amount : unsigned(3 downto 0);
	signal divide_clk : integer range 0 to N;
begin
    amount <= "0000";

	fsm : entity work.fsm
		port map(
			a => sw(1), 
			b => sw(0), 
			car_enter => inc, 
			car_exit => dec, 
			clk => clk, 
			reset => '0', 
			enable => enable
		);

    counter: entity work.free_run_bin_counter
        port map (
            clk => clk,
            reset => '0',
            inc => inc,
            dec => dec,
            enable => enable,
            q => res
        );

    display : entity work.disp_hex_mux
        port map(
            clk => clk, 
            reset => '0', 
            hex0 => res, 
            hex1 => "1111", 
            hex2 => "1111", 
            hex3 => "1111", 
            dp_in => "1111", 
            an => an, 
            sseg => sseg
        );

        enable <= '1' when divide_clk = N else '0';

        process (clk) begin
            if (clk'EVENT and clk = '1') then
                divide_clk <= divide_clk + 1;
                if divide_clk = N then
                    divide_clk <= 0;
                end if;
            end if;
        end process;

end arch;