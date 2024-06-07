transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/DFF_pos.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/adder4.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/add.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/student_num.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/dff4bits.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/design {C:/Users/user/Desktop/logic/one/fa_1bit/design/accumulator_top.sv}
vlog -sv -work work +incdir+C:/Users/user/Desktop/logic/one/fa_1bit/simulation/tb {C:/Users/user/Desktop/logic/one/fa_1bit/simulation/tb/tb_accumulator_top.sv}

