use work.dlx_types.all;
use work.bv_arithmetic.all;

entity alu is
	generic(prop_delay: Time:= 15 ns);
	port(operand1, operand2: in dlx_word; operation: in
		alu_operation_code;
		result: out dlx_word; error: out error_code);
end entity alu;

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