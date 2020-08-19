// subByte performs first transformation of encryption
module subByte(input  logic [127:0]noSubByte,
               output logic [127:0]subByte);

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
		
		sBox sb1(noSubByte[127:120], firstByte);
		sBox sb2(noSubByte[119:112], secondByte);
		sBox sb3(noSubByte[111:104], thirdByte);
		sBox sb4(noSubByte[103:96], fourthByte);
		sBox sb5(noSubByte[95:88], fifthByte);
		sBox sb6(noSubByte[87:80], sixthByte);
		sBox sb7(noSubByte[79:72], seventhByte);
		sBox sb8(noSubByte[71:64], eigthByte);
		sBox sb9(noSubByte[63:56], ninthByte);
		sBox sb10(noSubByte[55:48], tenthByte);
		sBox sb11(noSubByte[47:40], eleventhByte);
		sBox sb12(noSubByte[39:32], twelfthByte);
		sBox sb13(noSubByte[31:24], thirteenthByte);
		sBox sb14(noSubByte[23:16], fourteenthByte);
		sBox sb15(noSubByte[15:8], fifteenthByte);
		sBox sb16(noSubByte[7:0], sixteenthByte);
		
		assign subByte = {firstByte, secondByte, thirdByte, fourthByte, fifthByte,
								sixthByte, seventhByte, eigthByte, ninthByte, tenthByte,
								eleventhByte, twelfthByte, thirteenthByte, fourteenthByte,
								fifteenthByte, sixteenthByte};

endmodule
