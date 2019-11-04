use work.dlx_types.all;
use work.bv_arithmetic.all;

entity dlx_register is 
	generic(prop_delay: Time := 10 ns);
	port(in_val: in dlx_word; clock: in bit; out_val: out dlx_word);
end entity dlx_register;

architecture behaviour of dlx_register is
begin
	register_write: process(in_val, clock) is
	begin
		if clock = '1' then
			out_val <=  in_val after prop_delay;
		end if;
	end process register_write;
end architecture behaviour;

use work.dlx_types.all;
use work.bv_arithmetic.all;

entity reg_file is
	generic(prop_delay: Time := 15 ns);
	port(data_in: in dlx_word; readnotwrite, clock: in bit; data_out: out dlx_word; regnumber: in register_index);
end entity reg_file;

architecture behaviour of reg_file is
begin
	readwrite: process(data_in, regnumber, clock) is
	
	type reg_type is array (0 to 31) of dlx_word;
	variable registers: reg_type;

	begin
		if clock = '1' then
			if readnotwrite = '1' then
				data_out <= registers(bv_to_natural(regnumber)) after prop_delay;
			else
				registers(bv_to_natural(regnumber)) := data_in;
			end if;
		end if;
	end process readwrite;
end architecture behaviour;

use work.dlx_types.all;
use work.bv_arithmetic.all;

entity mux is
	generic(prop_delay: Time := 5 ns);
	port(input_1, input_0: in dlx_word; which: in bit; output: out dlx_word);
end entity mux;

architecture behaviour of mux is
begin
	plex: process(input_1, input_0, which) is
	begin
		if which = '1' then
			output <= input_1 after prop_delay;
		else
			output <= input_0 after prop_delay;
		end if;
	end process plex; 
end architecture behaviour;

use work.dlx_types.all;
use work.bv_arithmetic.all;

entity threeway_mux is
	generic(prop_delay: Time := 5 ns);
	port(input_2, input_1
, input_0: in dlx_word; which: in threeway_muxcode;
	output: out dlx_word);
end entity threeway_mux;

architecture behaviour of threeway_mux is
begin
	three_mux: process(input_2, input_1, input_0, which)
	
	variable eq: integer;

	begin
		eq := bv_to_integer(which);
		if eq = 0 then
			output <= input_0 after prop_delay;
		elsif eq = 1 then
			output <= input_1 after prop_delay;
		else
			output <= input_2 after prop_delay;
		end if;
	end process three_mux;
end architecture behaviour;

use work.dlx_types.all;
use work.bv_arithmetic.all;

entity pcplusone is
	generic(prop_delay: Time := 5 ns);
	port(input: in dlx_word; clock: in bit; output: out dlx_word);
end entity pcplusone;

architecture behaviour of pcplusone is
begin
	addone: process(input, clock) is
	begin
		if clock = '1' then
			if bv_to_integer(input) = 16#FFFFFFFF# then
				output <= integer_to_bv(0,input'length) after prop_delay; 
			else
				output <= bv_addu(input,integer_to_bv(1,input'length)) after prop_delay;
			end if;
		end if;
	end process addone;
end architecture behaviour;