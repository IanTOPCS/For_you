module seven_segment(//七段顯示器
	input logic [3:0]in,//輸入4bits
	output logic [6:0]out//輸出對應
);
 
assign out[6] = ((~in[3])&(~in[2])&(~in[1]))|(in[3]&in[2]&(~in[1])&(~in[0]))|((~in[3])&in[2]&in[1]&in[0]);
//g = (a3' and a2' and a1') or (a3 and a2 and a1' and a0') or (a3' and a2 and a1 and a0)


assign out[5] = ((~in[3])&(~in[2])&in[0])|((~in[3])&(~in[2])&in[1])|((~in[3])&in[1]&in[0])|(in[3]&in[2]&(~in[1])&in[0]);
//f = (a3' and a2' and a0) or (a3' and a2' and a1) or (a3' and a1 and a0) or (a3 and a2 and a1' and a0)

assign out[4] = ((~in[3])&in[0])|((~in[3])&in[2]&(~in[1]))|((~in[2])&(~in[1])&in[0]);
//e = (a3' and a0) or (a3' and a2 and a1') or (a2' and a1' and a0)

assign out[3] = ((~in[3])&(~in[2])&(~in[1])&in[0])|((~in[3])&in[2]&(~in[1])&(~in[0]))|(in[2]&in[1]&in[0])|(in[3]&(~in[2])&in[1]&(~in[0]));
//d = (a3' and a2 and a1' and a0') or (a3' and a2 and a1' and a0') or (a2 and a1 and a0) or (a3 and a2' and a1 and a0')

assign out[2] = (in[3]&in[2]&(~in[0]))|(in[3]&in[2]&in[1])|((~in[3])&(~in[2])&in[1]&(~in[0]));
//c = (a3 and a2 and a0') or (a3 and a2 and a1) or (a3' and a2' and a1 and a0')

assign out[1] = (in[3]&in[2]&(~in[0]))|((~in[3])&in[2]&(~in[1])&in[0])|(in[3]&in[1]&in[0])|(in[2]&in[1]&(~in[0]));
//b = (a3 and a1 and a0') or (a3' and a2 and a1' and a0) or (a3 and a1 and a0) or (a2 and a1 and a0') 

assign out[0] = ((~in[3])&(~in[2])&(~in[1])&in[0])|((~in[3])&in[2]&(~in[1])&(~in[0]))|(in[3]&in[2]&(~in[1])&in[0])|(in[3]&(~in[2])&in[1]&in[0]);
//a = (a3' and a2' and a1' and a0) or (a3' and a2 and a1' and a0') or (a3 and a2 and a1' and a0) or (a3 and a2' and a1 and a0)

endmodule
