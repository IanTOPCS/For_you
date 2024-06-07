module mul(
	input [1:0] sel,//the select input
	input [3:0] in,//the choose of in
	output logic ans//4 to one output
);
logic [1:0] false;//select's not output
not(false[1], sel[1]);
not(false[0], sel[0]);

logic [3:0] tmp;
logic [3:0] tmp_ans;


and (tmp[0], false[1], false[0]);//a'&b'&(in[0])
and (tmp_ans[0], tmp[0], in[0]);

and (tmp[1], false[1], sel[0]);//a'&b&(in[1])
and (tmp_ans[1], tmp[1], in[1]);

and (tmp[2], sel[1], false[0]);//a&b'&(in[2])
and (tmp_ans[2], tmp[2], in[2]);

and (tmp[3], sel[1], sel[0]);//a&b&(in[3])
and (tmp_ans[3], tmp[3], in[3]);

logic [1:0] or_ans;//put answer with or the output of above four
or (or_ans[1], tmp_ans[2], tmp_ans[3]);
or (or_ans[0], tmp_ans[0], tmp_ans[1]);
or (ans, or_ans[0], or_ans[1]);
endmodule
