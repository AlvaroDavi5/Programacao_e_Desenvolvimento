library ieee;
use ieee.std_logic_1164.all;


entity fsm is
	port (
		a          : in std_logic;
		b          : in std_logic;
		clk, reset : in std_logic;
		enable     : in std_logic;
		car_enter  : out std_logic;
		car_exit   : out std_logic
	);
end fsm;

architecture arch of fsm is
	type eg_state_type is (N, IA, IAB, IB, CI, OB, OAB, OA, CO);
	signal state_reg, state_next : eg_state_type;
begin
	-- state register
	process (clk, reset)
	begin
		if (reset = '1') then
			state_reg <= N;
		elsif (clk'event and clk = '1') then -- clock rising edge
			if (enable = '1') then
				state_reg <= state_next; -- state change
			end if;
		end if;
	end process;

	-- next-state logic
	process (state_reg, a, b, enable)
	begin
		case state_reg is
			-- initial/normal state
			when N =>
				if a = '0' and b = '1' then
					state_next <= OB; -- next state (exit flux)
				elsif a = '1' then
					state_next <= IA; -- next state (enter)
				else
					state_next <= N; -- current state
				end if;

			-- enter flux
			when IA =>
				if a = '1' and b = '1' then
					state_next <= IAB; -- next state
				elsif a = '1' and b = '0' then
					state_next <= IA; -- current state
				elsif a = '0' then
					state_next <= N; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;
			when IAB =>
				if a = '0' and b = '1' then
					state_next <= IB; -- next state
				elsif a = '1' and b = '1' then
					state_next <= IAB; -- current state
				elsif b = '0' then
					state_next <= IA; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;
			when IB =>
				if a = '0' and b = '0' then
					state_next <= CI; -- next state
				elsif a = '0' and b = '1' then
					state_next <= IB; -- current state
				elsif a = '1' then
					state_next <= IAB; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;

			-- exit flux
			when OB =>
				if a = '1' and b = '1' then
					state_next <= OAB; -- next state
				elsif a = '0' and b = '1' then
					state_next <= OB; -- current state
				elsif b = '0' then
					state_next <= N; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;
			when OAB =>
				if a = '1' and b = '0' then
					state_next <= OA; -- next state
				elsif a = '1' and b = '1' then
					state_next <= OAB; -- current state
				elsif a = '0' then
					state_next <= OB; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;
			when OA =>
				if a = '0' and b = '0' then
					state_next <= CO; -- next state
				elsif a = '1' and b = '0' then
					state_next <= OA; -- current state
				elsif b = '1' then
					state_next <= OAB; -- previous state
				else
					state_next <= state_reg; -- current state
				end if;

			-- return flux
			when others => -- N, CI, CO
				if enable = '1' then
					state_next <= N;
				else
					state_next <= state_reg;
				end if;
		end case;
	end process;

	-- Moore output logic
	process (state_reg)
	begin
		case state_reg is
			when CI =>
				car_enter <= '1';
				car_exit <= '0';
			when CO =>
				car_enter <= '0';
				car_exit <= '1';
			when others =>
				car_enter <= '0';
				car_exit <= '0';
		end case;
	end process;

end arch;
