--=============================
-- Listing 4.3
--=============================
library ieee;
use ieee.std_logic_1164.all;
entity subtractor is
   port(
      num_a, num_b, ci : in std_logic;
      res, co: out std_logic
   );
end subtractor;


architecture arch of subtractor is
begin
   process(shift)
   begin
      case shift is
         when "100"|"101"|"110"|"111" =>
            code <= "11";
         when "010"|"011" =>
            code <= "10";
         when "001" =>
            code <= "01";
         when others =>
            code <= "00";
      end case;
   end process;
end arch;
