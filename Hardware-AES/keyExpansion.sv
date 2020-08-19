// keyExpansion routine to generate key schedule
module keyExpansion(input  logic [127:0]calculatedKey,
		input  logic [3:0]currentRound,
                output logic [127:0]oldKey);
						  
		logic [31:0]temp;
		logic [31:0]rotatedTemp;
		logic [31:0]subTemp;
		logic [31:0]Rcon;
		logic [31:0]rconTemp;
		
		assign temp = calculatedKey[31:0];
		
		// rotate temp
		rotWord r1(temp, rotatedTemp);
		
		// substitute rotatedTemp
		subWord sw1(rotatedTemp, subTemp);
		
		// set Rcon according to round
		getRcon gr1(currentRound, Rcon);
		
		// subTemp XOR Rcon
		assign rconTemp = subTemp ^ Rcon;
		
		// rconTemp XOR w0
		assign oldKey[127:96] = rconTemp ^ calculatedKey[127:96];
		
		// oldKey[127:96] XOR w1
		assign oldKey[95:64] = oldKey[127:96] ^ calculatedKey[95:64];
		
		// oldKey[95:64] XOR w2
		assign oldKey[63:32] = oldKey[95:64] ^ calculatedKey[65:32];
		
		// oldKey[63:32] XOR w3
		assign oldKey[31:0] = oldKey[63:32] ^ calculatedKey[31:0];
		
endmodule

// rotate word 
module rotWord(input  logic [31:0]inWord,
	       output logic [31:0]rotatedWord);
		
		// [a0, a1, a2, a3] = [a1, a2, a3, a0]
		assign rotatedWord = {inWord[23:16], inWord[15:8], inWord[7:0], inWord[31:24]};
					
endmodule

// substitute word using sBox
module subWord(input  logic [31:0]inWord,
					output logic [31:0]substitutedWord);
					
		logic [7:0]firstByte;
		logic [7:0]secondByte;
		logic [7:0]thirdByte;
		logic [7:0]fourthByte;
		
		sBox sb17(inWord[31:24], firstByte);
		sBox sb18(inWord[23:16], secondByte);
		sBox sb19(inWord[15:8], thirdByte);
		sBox sb20(inWord[7:0], fourthByte);
		
		assign substitutedWord = {firstByte, secondByte, thirdByte, fourthByte};
					
endmodule					

// updates Rcon for current round
module getRcon(input  logic [3:0]currentRound,
					output logic [31:0]Rcon);
					
		always_comb 			
			case(currentRound)
				4'b0001: Rcon <= 32'h01000000;
				4'b0010: Rcon <= 32'h02000000;
				4'b0011: Rcon <= 32'h04000000;
				4'b0100: Rcon <= 32'h08000000;
				4'b0101: Rcon <= 32'h10000000;
				4'b0110: Rcon <= 32'h20000000;
				4'b0111: Rcon <= 32'h40000000;
				4'b1000: Rcon <= 32'h80000000;
				4'b1001: Rcon <= 32'h1B000000;
				4'b1010: Rcon <= 32'h36000000;
				default  Rcon <= 32'h00000000;
			endcase
					
endmodule 


