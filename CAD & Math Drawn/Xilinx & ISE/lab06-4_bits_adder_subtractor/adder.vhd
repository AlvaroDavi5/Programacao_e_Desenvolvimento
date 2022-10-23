--=============================
-- Listing 4.3
--=============================
library ieee;
use ieee.std_logic_1164.all;
entity adder is
   port(
      num_a, num_b : in std_logic;
      res, co: out std_logic
   );
end adder;


architecture arch of adder is
begin
   co <= num_a and num_b;
   res <= num_a xor num_b;
end arch;
