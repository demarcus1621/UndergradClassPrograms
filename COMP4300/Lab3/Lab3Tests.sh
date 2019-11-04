# Author: Demarcus Campbell
# Lab 3: Data Path test cases

# Test dlx_register
vsim work.dlx_register
add wave -position insertpoint sim:/dlx_register/*
force -freeze sim:/dlx_register/clock 1 0
force -freeze sim:/dlx_register/in_val 32'hf0f0f0f0 0
run

force -freeze sim:/dlx_register/in_val 32'h00000000 0
force -freeze sim:/dlx_register/clock 0 0
run
pause
quit -sim

# Test reg_file
vsim work.reg_file
add wave -position insertpoint sim:/reg_file/*
force -freeze sim:/reg_file/data_in 32'hf0f0f0f0 0
force -freeze sim:/reg_file/readnotwrite 0 0
force -freeze sim:/reg_file/regnumber 5'h11 0
force -freeze sim:/reg_file/clock 1 0, 0 {25 ns} -r 50
run
force -freeze sim:/reg_file/readnotwrite 1 0
run
pause
quit -sim

#Test two-way multiplexer 
vsim work.mux
add wave -position insertpoint sim:/mux/*
force -freeze sim:/mux/input_0 32'hFFFFFFFF 0
force -freeze sim:/mux/input_1 32'hf0f0f0f0 0
force -freeze sim:/mux/which 0 0
run
force -freeze sim:/mux/which 1 0
run
pause
quit -sim 

#Test three-way multiplexer
vsim work.threeway_mux
add wave -position insertpoint sim:/threeway_mux/*
force -freeze sim:/threeway_mux/input_2 32'h0f0f0f0f 0
force -freeze sim:/threeway_mux/input_1 32'hf0f0f0f0 0
force -freeze sim:/threeway_mux/input_0 32'hFFFFFFFF 0
force -freeze sim:/threeway_mux/which 2'h0
run
force -freeze sim:/threeway_mux/which 2'h1
run
force -freeze sim:/threeway_mux/which 2'h2
run
pause
quit -sim

#Test Program Counter Increment
vsim work.pcplusone
add wave -position insertpoint sim:/pcplusone/*
force -freeze sim:/pcplusone/input 32'hFFFFFFFF 0 
force -freeze sim:/pcplusone/clock 1 0
run
force -freeze sim:/pcplusone/clock 0 0
run
force -freeze sim:/pcplusone/input 32'h00000000
force -freeze sim:/pcplusone/clock 1 0
run
