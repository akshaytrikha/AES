// addRoundKey performs second transformation of encryption
module addRoundKey(input  logic [127:0]noAddRoundKey,
                  input   logic [127:0]calculatedKey,
                  output  logic [127:0]addRoundKey);

      assign addRoundKey = noAddRoundKey ^ calculatedKey;

endmodule
