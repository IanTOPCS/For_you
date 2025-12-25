transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+D:/DE0_CV/design {D:/DE0_CV/design/DE0_CV.sv}
vlog -sv -work work +incdir+D:/DE0_CV/design {D:/DE0_CV/design/sub_4bit.sv}

