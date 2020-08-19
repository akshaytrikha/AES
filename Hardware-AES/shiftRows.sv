// shiftRows performs second transformation of encryption
module shiftRows(input  logic [127:0]noShiftRows,
                 output logic [127:0]shiftRows);

      logic [7:0]firstByte;
		logic [7:0]secondByte;
		logic [7:0]thirdByte;
		logic [7:0]fourthByte;
		logic [7:0]fifthByte;
		logic [7:0]sixthByte;
		logic [7:0]seventhByte;
		logic [7:0]eigthByte;
		logic [7:0]ninthByte;
		logic [7:0]tenthByte;
		logic [7:0]eleventhByte;
		logic [7:0]twelfthByte;
		logic [7:0]thirteenthByte;
		logic [7:0]fourteenthByte;
		logic [7:0]fifteenthByte;
		logic [7:0]sixteenthByte;
		
		assign firstByte = noShiftRows[127:120];
		assign secondByte = noShiftRows[119:112];
		assign thirdByte = noShiftRows[111:104];
		assign fourthByte = noShiftRows[103:96];
		assign fifthByte = noShiftRows[95:88];
		assign sixthByte = noShiftRows[87:80];
		assign seventhByte = noShiftRows[79:72];
		assign eigthByte = noShiftRows[71:64];
		assign ninthByte = noShiftRows[63:56];
		assign tenthByte = noShiftRows[55:48];
		assign eleventhByte = noShiftRows[47:40];
		assign twelfthByte = noShiftRows[39:32];
		assign thirteenthByte = noShiftRows[31:24];
		assign fourteenthByte = noShiftRows[23:16];
		assign fifteenthByte = noShiftRows[15:8];
		assign sixteenthByte = noShiftRows[7:0];
		
		// "State" (cypherText / key) encoding
		//        [127:120] [95:88] [63:56] [31:24]     S0,0    S0,1    S0,2    S0,3
		//        [119:112] [87:80] [55:48] [23:16]     S1,0    S1,1    S1,2    S1,3
		//        [111:104] [79:72] [47:40] [15:8]      S2,0    S2,1    S2,2    S2,3
		//        [103:96]  [71:64] [39:32] [7:0]       S3,0    S3,1    S3,2    S3,3
		
		assign shiftRows[127:96] = {firstByte, sixthByte, eleventhByte, sixteenthByte};
		assign shiftRows[95:64] = {fifthByte, tenthByte, fifteenthByte, fourthByte};
		assign shiftRows[63:32] = {ninthByte, fourteenthByte, thirdByte, eigthByte};
		assign shiftRows[31:0] 	= {thirteenthByte, secondByte, seventhByte, twelfthByte};

endmodule
