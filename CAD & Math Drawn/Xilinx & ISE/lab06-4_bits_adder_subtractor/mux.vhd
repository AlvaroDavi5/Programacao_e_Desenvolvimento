--=============================
-- Listing 4.3
--=============================
library ieee;
use ieee.std_logic_1164.all;
entity mux is
   port(
      op : std_logic;
      b0, b1 : in std_logic_vector(3 downto 0);
      b_res : out std_logic_vector(3 downto 0)
   );
end mux;


architecture arch of mux is
begin
   process(op)
   begin
      case op is
         when '1' => -- subtraction
            b_res <= b1;
         when others => -- adition
            b_res <= b0;
      end case;
   end process;
end arch;
