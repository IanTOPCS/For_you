module new_decorder(
	input [2:0]in,
	output [7:0]f
);
logic [2:0]not_in;
not(not_in[2], in[2]);
not(not_in[1], in[1]);
not(not_in[0], in[0]);
logic [7:0]tmp;

and(tmp[7], not_in[0], not_in[1]);//x'&y'&z'
and(f[7], not_in[2], tmp[7]);

and(tmp[6], not_in[2], not_in[1]);//x'&y'&z
and(f[6], tmp[6], in[0]);

and(tmp[5], not_in[2], in[1]);//x'&y&z'
and(f[5], tmp[5], not_in[0]);

and(tmp[4], not_in[2], in[1]);//x'&y&z
and(f[4], tmp[4], in[0]);

and(tmp[3], in[2], not_in[1]);//x&y'&z'
and(f[3], tmp[3], not_in[0]);

and(tmp[2], in[2], not_in[1]);//x&y'&z
and(f[2], tmp[2], in[0]);

and(tmp[1], in[2], in[1]);//x&y&z'
and(f[1], tmp[1], not_in[0]);

and(tmp[0], in[2], in[1]);//x&y&z
and(f[0], tmp[0], in[0]);

endmodule
