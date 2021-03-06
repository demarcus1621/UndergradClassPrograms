-- datapath_aubie.vhd

-- entity reg_file (lab 2)
use work.dlx_types.all; 
use work.bv_arithmetic.all;  

entity reg_file is
     generic(prop_delay: Time := 5 ns);
     port (data_in: in dlx_word; readnotwrite,clock : in bit; 
	   data_out: out dlx_word; reg_number: in register_index );
end entity reg_file; 

architecture behaviour of reg_file is
begin
	readwrite: process(data_in, reg_number, clock) is
	
	type reg_type is array (0 to 31) of dlx_word;
	variable registers: reg_type;

	begin
		if clock = '1' then
			if readnotwrite = '1' then
				data_out <= registers(bv_to_natural(reg_number)) after prop_delay;
			else
				registers(bv_to_natural(reg_number)) := data_in;
			end if;
		end if;
	end process readwrite;
end architecture behaviour;

-- entity alu (lab 3) 
use work.dlx_types.all; 
use work.bv_arithmetic.all; 

entity alu is 
     generic(prop_delay : Time := 5 ns);
     port(operand1, operand2: in dlx_word; operation: in alu_operation_code; 
          result: out dlx_word; error: out error_code); 
end entity alu; 

-- alu_operation_code values
-- 0000 unsigned add
-- 0001 signed add
-- 0010 2's compl add
-- 0011 2's compl sub
-- 0100 2's compl mul
-- 0101 2's compl divide
-- 0110 logical and
-- 0111 bitwise and
-- 1000 logical or
-- 1001 bitwise or
-- 1010 logical not (op1) 
-- 1011 bitwise not (op1)
-- 1100-1111 output all zeros

-- error code values
-- 0000 = no error
-- 0001 = overflow (too big positive) 
-- 0010 = underflow (too small neagative) 
-- 0011 = divide by zero 
architecture behaviour of alu is
begin

	determine_opcode: process(operation, operand1, operand2) is -- Call proper function by opcode
	
	variable is_overflow: boolean;
	variable temp_result: bit_vector(31 downto 0);
	variable div_zero: boolean;
	
	begin
		case operation is
			when "0000" => -- unsigned add
				bv_addu(operand1, operand2, temp_result, is_overflow);
				result <= temp_result after prop_delay;
				if is_overflow then
					error <= integer_to_bv(1,4) after prop_delay;
				else
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0001" => -- unsigned subtract
				bv_subu(operand1, operand2, temp_result, is_overflow);
				result <= temp_result after prop_delay;
				if is_overflow then
					error <= integer_to_bv(2, 4) after prop_delay;
				else
					error <= integer_to_bv(0, 4) after prop_delay;
				end if;
			when "0010" => -- two's complement add
				bv_add(operand1, operand2, temp_result, is_overflow);
				result <= temp_result after prop_delay;
				if is_overflow then
					if operand1(operand1'left) = '0' and operand2(operand2'left) = '0' then
						error <= integer_to_bv(1,4) after prop_delay;
					else
						error <= integer_to_bv(2, 4) after prop_delay;
					end if;
				else
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0011" => -- two's complement subtract
				bv_sub(operand1, operand2, temp_result, is_overflow);
				result <= temp_result after prop_delay;
				if is_overflow then
					if operand1(operand1'left) = '0' then
						error <= integer_to_bv(1,4) after prop_delay;
					else
						error <= integer_to_bv(2,4) after prop_delay;
					end if;
				else
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0100" => -- two's complement multiply
				bv_mult(operand1, operand2, temp_result, is_overflow);
				result <= temp_result after prop_delay;
				if is_overflow then
					if operand1(operand1'left) = operand2(operand2'left) then
						error <= integer_to_bv(1,4) after prop_delay;
					else
						error <= integer_to_bv(2,4) after prop_delay;
					end if;
				else
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0101" => -- two's complement divide
				bv_div(operand1, operand2, temp_result, div_zero, is_overflow);
				result <= temp_result after prop_delay; 
				if div_zero then
					error <= integer_to_bv(3,4) after prop_delay;
				else
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0110" => -- logical AND (&&)
				if operand1 /= integer_to_bv(0, operand1'length) and operand2 /= integer_to_bv(0, operand2'length) then
					result <= integer_to_bv(1,operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				else
					result <= integer_to_bv(1,operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "0111" => -- bitwise AND (&)
				result <= operand1 and operand2 after prop_delay;
				error <= integer_to_bv(0,4) after prop_delay;
			when "1000" =>  -- logical OR (||)
				if operand1 /= integer_to_bv(0,operand1'length) or operand2 /= integer_to_bv(0,operand2'length) then
					result <= integer_to_bv(1, operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				else
					result <= integer_to_bv(0, operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "1001" => -- bitwise OR (|)
				result <= operand1 or operand2 after prop_delay;
				error <= integer_to_bv(0,4) after prop_delay;
			when "1010" => -- logical NOT (!)
				if operand1 /= integer_to_bv(0, operand1'length) then
					result <= integer_to_bv(1, operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				else
					result <= integer_to_bv(1, operand1'length) after prop_delay;
					error <= integer_to_bv(0,4) after prop_delay;
				end if;
			when "1011" => -- bitwise NOT (~)
				result <= not operand1 after prop_delay;
				error <= integer_to_bv(0,4) after prop_delay;
			when others =>  
				result <= integer_to_bv(0, 32) after prop_delay;
				error <= integer_to_bv(0, 4) after prop_delay;
		end case;
	end process determine_opcode;
end architecture behaviour;

-- entity dlx_register (lab 3)
use work.dlx_types.all; 

entity dlx_register is
     generic(prop_delay : Time := 5 ns);
     port(in_val: in dlx_word; clock: in bit; out_val: out dlx_word);
end entity dlx_register;

architecture behaviour of dlx_register is
begin
	operate : process(in_val, clock) is
	begin
		if clock = '1' then
			out_val <=  in_val after prop_delay;
		end if;
	end process operate;
end architecture behaviour;

-- entity pcplusone
use work.dlx_types.all;
use work.bv_arithmetic.all; 

entity pcplusone is
	generic(prop_delay: Time := 5 ns); 
	port (input: in dlx_word; clock: in bit;  output: out dlx_word); 
end entity pcplusone; 

architecture behavior of pcplusone is 
begin
	plusone: process(input,clock) is  -- add clock input to make it execute
		variable newpc: dlx_word;
		variable error: boolean; 
	begin
	   if clock'event and clock = '1' then
	  	bv_addu(input,"00000000000000000000000000000001",newpc,error);
		output <= newpc after prop_delay; 
	  end if; 
	end process plusone; 
end architecture behavior; 


-- entity mux
use work.dlx_types.all; 

entity mux is
     generic(prop_delay : Time := 5 ns);
     port (input_1,input_0 : in dlx_word; which: in bit; output: out dlx_word);
end entity mux;

architecture behavior of mux is
begin
   muxProcess : process(input_1, input_0, which) is
   begin
      if (which = '1') then
         output <= input_1 after prop_delay;
      else
         output <= input_0 after prop_delay;
      end if;
   end process muxProcess;
end architecture behavior;
-- end entity mux

-- entity threeway_mux 
use work.dlx_types.all; 

entity threeway_mux is
     generic(prop_delay : Time := 5 ns);
     port (input_2,input_1,input_0 : in dlx_word; which: in threeway_muxcode; output: out dlx_word);
end entity threeway_mux;

architecture behavior of threeway_mux is
begin
   muxProcess : process(input_2, input_1, input_0, which) is
   begin
      if (which = "10" or which = "11" ) then
         output <= input_2 after prop_delay;
      elsif (which = "01") then 
	 output <= input_1 after prop_delay; 
       else
         output <= input_0 after prop_delay;
      end if;
   end process muxProcess;
end architecture behavior;
-- end entity mux

  
-- entity memory
use work.dlx_types.all;
use work.bv_arithmetic.all;

entity memory is
  
  port (
    address : in dlx_word;
    readnotwrite: in bit; 
    data_out : out dlx_word;
    data_in: in dlx_word; 
    clock: in bit); 
end memory;

architecture behavior of memory is

begin  -- behavior

  mem_behav: process(address,clock) is
    -- note that there is storage only for the first 1k of the memory, to speed
    -- up the simulation
    type memtype is array (0 to 1024) of dlx_word;
    variable data_memory : memtype;
  begin
    -- fill this in by hand to put some values in there
    -- some instructions
    data_memory(0) :=  X"30200000"; --LD R4, 0x100
    data_memory(1) :=  X"00000100"; -- address 0x100 for previous instruction
    data_memory(2) :=  "00000000000110000100010000000000"; -- ADDU R3,R1,R2
    -- some data
    -- note that this code runs every time an input signal to memory changes, 
    -- so for testing, write to some other locations besides these
    data_memory(256) := "01010101000000001111111100000000";
    data_memory(257) := "10101010000000001111111100000000";
    data_memory(258) := "00000000000000000000000000000001";


   
    if clock = '1' then
      if readnotwrite = '1' then
        -- do a read
        data_out <= data_memory(bv_to_natural(address)) after 5 ns;
      else
        -- do a write
        data_memory(bv_to_natural(address)) := data_in; 
      end if;
    end if;


  end process mem_behav; 

end behavior;
-- end entity memory


