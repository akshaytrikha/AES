// controller sends out enable signals for control path
module controller(input  logic clk,
                  input  logic load,
                  output logic cypherTextOn,
                  output logic subByteOn,
                  output logic shiftRowsOn,
                  output logic mixColumnsOn,
                  output logic keyExpansionOn,
                  output logic addRoundKeyOn,
						output logic [3:0]currentRound,
                  output logic done);
		
		// bus to neatly keep track of enable signals at each state
		logic [5:0]enableSignals;

        // FSM for AES rounds
      typedef enum logic [11:0] {round1, round2, round3, round4, round5, round6, round7, round8, round9, round10, round11, round12} statetype;
      statetype round, nextRound;

      // state register
	    // flip flop that updates state on rising clock edge
	    always_ff @(posedge clk)
          // reset on load
		      if (load) round <= round1;
		      else round <= nextRound;

      // next state logic
    	always_comb
    	    case(round)
					round1:    begin 
										nextRound <= round2;
										enableSignals <= 6'b100001;
										currentRound <= 4'b0001;
								  end 
								  
					round2:    begin 
										nextRound <= round3;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0010;
								  end 
									
					round3:    begin
										nextRound <= round4;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0011;
								  end
								  
					round4:    begin
										nextRound <= round5;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0100;
								  end
								  
					round5:    begin
										nextRound <= round6;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0101;
								  end
								  
					round6:    begin
										nextRound <= round7;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0110;
								  end
								  
					round7:    begin
										nextRound <= round8;
										enableSignals <= 6'b011111;
										currentRound <= 4'b0111;
								  end
								  
					round8:    begin
										nextRound <= round9;
										enableSignals <= 6'b011111;
										currentRound <= 4'b1000;
								  end
								  
					round9:    begin
										nextRound <= round10;
										enableSignals <= 6'b011111;
										currentRound <= 4'b1001;
								  end
								  
					round10:   begin
										nextRound <= round11;
										enableSignals <= 6'b011111;
										currentRound <= 4'b1010;
								  end
								  
					round11:   begin
										nextRound <= round12;
										enableSignals <= 6'b011011;
										currentRound <= 4'b1011;
								  end
								  
					// additional round to assert done and push out cypherText on last flop			  
					round12:	  begin
										nextRound <= round12;
										enableSignals <= 6'b000000;
										currentRound <= 4'b1100;
								  end

              default:    begin
										nextRound <= round1;
										enableSignals <= 6'b000000;
										currentRound <= 4'b0000;
								  end 
          endcase
			 
		assign cypherTextOn = enableSignals[5];
		assign subByteOn = enableSignals[4];
		assign shiftRowsOn = enableSignals[3];
		assign mixColumnsOn = enableSignals[2];
		assign keyExpansionOn = enableSignals[1];
		assign addRoundKeyOn = enableSignals[0];

      assign done = (round == round12);

endmodule
