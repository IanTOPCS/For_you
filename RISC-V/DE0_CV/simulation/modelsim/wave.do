onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider {TOP LEVEL INPUTS}
add wave -noupdate -radix hexadecimal /testbench/cpu/clk
add wave -noupdate -radix hexadecimal /testbench/cpu/rst
add wave -noupdate -divider PC
add wave -noupdate -radix hexadecimal /testbench/cpu/jump_addr_
add wave -noupdate -radix hexadecimal /testbench/cpu/pc
add wave -noupdate -divider IF/ID
add wave -noupdate -radix hexadecimal /testbench/cpu/inst_r
add wave -noupdate -divider INST_DEC
add wave -noupdate -radix hexadecimal /testbench/cpu/opcode_
add wave -noupdate -radix hexadecimal /testbench/cpu/funct3_
add wave -noupdate -radix hexadecimal /testbench/cpu/funct7_
add wave -noupdate -divider REG_FILE
add wave -noupdate -radix hexadecimal {/testbench/cpu/myreg/regs[2]}
add wave -noupdate -radix hexadecimal {/testbench/cpu/myreg/regs[3]}
add wave -noupdate -radix hexadecimal {/testbench/cpu/myreg/regs[4]}
add wave -noupdate -radix hexadecimal {/testbench/cpu/myreg/regs[5]}
add wave -noupdate -divider FSM
add wave -noupdate -radix hexadecimal /testbench/cpu/mycontroller/ps
add wave -noupdate -divider ALU
add wave -noupdate -radix hexadecimal /testbench/cpu/rd_value_
add wave -noupdate -divider FSM
add wave -noupdate -divider ...
add wave -noupdate /testbench/cpu/rst_pc_
add wave -noupdate /testbench/cpu/pc_r
add wave -noupdate /testbench/cpu/flush_IFID_
add wave -noupdate /testbench/cpu/rst_or_flush_IFID_r
add wave -noupdate /testbench/cpu/write_regf_en_r
add wave -noupdate /testbench/cpu/rs1_value
add wave -noupdate /testbench/cpu/rs2_value
add wave -noupdate /testbench/cpu/flush_IDEX_
add wave -noupdate /testbench/cpu/op_
add wave -noupdate /testbench/cpu/op_r
add wave -noupdate /testbench/cpu/write_regf_en_
add wave -noupdate /testbench/cpu/rst_or_flush_IDEX_r
add wave -noupdate -radix hexadecimal /testbench/cpu/imm_r
add wave -noupdate -radix hexadecimal /testbench/cpu/rs1_value_r
add wave -noupdate -radix hexadecimal /testbench/cpu/rs2_value_r
add wave -noupdate -radix hexadecimal /testbench/cpu/imm_r
add wave -noupdate /testbench/cpu/sel_rd_value_
add wave -noupdate /testbench/cpu/sel_rd_value_r
add wave -noupdate -radix hexadecimal /testbench/cpu/mul_out
add wave -noupdate -radix hexadecimal /testbench/cpu/div_out
add wave -noupdate -radix hexadecimal /testbench/cpu/read_data
add wave -noupdate -radix hexadecimal /testbench/cpu/lsu1/ram_0/ram
add wave -noupdate -radix hexadecimal /testbench/cpu/lsu1/ram_1/ram
add wave -noupdate -radix hexadecimal /testbench/cpu/lsu1/ram_2/ram
add wave -noupdate -radix hexadecimal /testbench/cpu/lsu1/ram_3/ram
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {233200 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 165
configure wave -valuecolwidth 65
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {1432300 ps}
