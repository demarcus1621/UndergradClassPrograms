entity andOrSwitch is
	generic(prop_delay: Time:= 10 ns);
	port(a_in, b_in, control: in bit;
		result: out bit); 
end entity andOrSwitch;

architecture behaviour1 of andOrSwitch is
begin
	switch : process(a_in, b_in, control) is
	begin
		if control = '1' then -- When control is equal to 1 we use AND gate 
			if a_in = '1' then
				if b_in = '1' then
					result <= '1' after prop_delay;  -- 1 && 1 = 1
				else
					result <= '0' after prop_delay;  -- 1 && 0 = 0
				end if;
			else
				result <= '0' after prop_delay;  -- 0 && 1/0 = 0 
			end if;
		else  -- When control is equal to 0 we use OR gate
			if a_in = '1' then 
				if b_in = '1' then
					result <= '1' after prop_delay; -- 1 || 1 = 1
				else
					result <= '1' after prop_delay; -- 1 || 0 = 1
				end if;
			else
				if b_in = '1' then
					result <= '1' after prop_delay; -- 0 || 1 = 1
				else
					result <= '0' after prop_delay; -- 0 || 0 = 0
				end if;
			end if;
		end if;
	end process switch;
end architecture behaviour1;