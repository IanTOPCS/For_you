`timescale 1ns/1ps
module testbench;

	logic [2:0] a [0:7];
	logic [2:0] sel;
	logic [2:0] y;
	
	mux	u_mux(
		.a		(a),
		.sel	(sel),
		.y		(y)
	);

	initial begin
		#10 begin
			a[0] = 3'd0;
			a[1] = 3'd1;
			a[2] = 3'd2;
			a[3] = 3'd3;
			a[4] = 3'd4;
			a[5] = 3'd5;
			a[6] = 3'd6;
			a[7] = 3'd7;
		end
		#10 sel = 0;
		#10 sel = 1;
		#10	sel = 2;
		#10 sel = 3;
		#10 sel = 4;
		#10 sel = 5;
		#10 sel = 6;
		#10 sel = 7;
		#100 $stop;
	end
endmodule