library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top is
    Port ( clk : in STD_LOGIC;
           led : out STD_LOGIC_VECTOR (8 downto 0));
end top;

architecture lab8 of top is
constant N : integer := 99999998; 
signal enable : std_logic;
signal divide_clk : integer range 0 to N;

begin
bin_counter_unit_0 : entity work.free_run_bin_counter
      port map(
                clk      => clk,
                reset    => '0',
                enable   => enable,
                max_tick => led(3),
                q        => led(2 downto 0)
                );
    
     enable <= '1' when divide_clk = N else '0';

     PROCESS (clk)
        BEGIN
            IF (clk'EVENT AND clk='1') THEN
                divide_clk <= divide_clk+1;
                IF divide_clk = N THEN
                    divide_clk <= 0;
                END IF;
            END IF;
     END PROCESS;

end lab8;
