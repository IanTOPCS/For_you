vsim -voptargs=+acc work.tb_accumulator_top
view structure wave signals

do wave.do

log -r *
run -all

