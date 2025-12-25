transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/RAM.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/Reg_file.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/Program_Rom.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/mydefine.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/MUL.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/DIV.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/mylsu.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/mycpu.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/myalu.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/INST_DEC.sv}
vlog -sv -work work +incdir+C:/Users/Magician/Desktop/RISC-V/DE0_CV/design {C:/Users/Magician/Desktop/RISC-V/DE0_CV/design/controller.sv}

