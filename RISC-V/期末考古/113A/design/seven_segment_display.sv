`timescale 1ns/100ps
module seven_segment_display(
    input logic [3:0] digit,   // 4位元二進制數字輸入
    output logic [6:0] seg     // 7段顯示器輸出 (g, f, e, d, c, b, a)
);
	//共陽
    always_comb begin
        case (digit)
            4'h0: seg = 7'b1000000;  	// 顯示 "0"
            4'h1: seg = 7'b1111001;  	// 顯示 "1"
            4'h2: seg = 7'b0100100;  	// 顯示 "2"
            4'h3: seg = 7'b0110000;  	// 顯示 "3"
            4'h4: seg = 7'b0011001;  	// 顯示 "4"
            4'h5: seg = 7'b0010010;  	// 顯示 "5"
            4'h6: seg = 7'b0000010;  	// 顯示 "6"
            4'h7: seg = 7'b1111000;  	// 顯示 "7"
            4'h8: seg = 7'b0000000;  	// 顯示 "8"
            4'h9: seg = 7'b0010000;  	// 顯示 "9"
            4'ha: seg = 7'b0001000; 	// 顯示 "A"
            4'hb: seg = 7'b0000011; 	// 顯示 "B"
            4'hc: seg = 7'b1000110; 	// 顯示 "C"
            4'hd: seg = 7'b0100001; 	// 顯示 "D"
            4'he: seg = 7'b0000110; 	// 顯示 "E"
            4'hf: seg = 7'b0001110; 	// 顯示 "F"
            default: seg = 7'b1111111; 	// 不顯示
        endcase
    end

endmodule


