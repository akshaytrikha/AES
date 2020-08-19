/////////////////////////////////////////////
// mixcolumns
//   Even funkier action on columns
//   Section 5.1.3, Figure 9
//   Same operation performed on each of four columns
/////////////////////////////////////////////

module mixColumns(input  logic [127:0]noMixColumns,
                  output logic [127:0]mixColumns);

  mixColumn mc0(noMixColumns[127:96], mixColumns[127:96]);
  mixColumn mc1(noMixColumns[95:64],  mixColumns[95:64]);
  mixColumn mc2(noMixColumns[63:32],  mixColumns[63:32]);
  mixColumn mc3(noMixColumns[31:0],   mixColumns[31:0]);
endmodule

/////////////////////////////////////////////
// mixcolumn
//   Perform Galois field operations on bytes in a column
//   See EQ(4) from E. Ahmed et al, Lightweight Mix Columns Implementation for AES, AIC09
//   for this hardware implementation
/////////////////////////////////////////////

module mixColumn(input  logic [31:0] a,
                 output logic [31:0] y);
                      
        logic [7:0] a0, a1, a2, a3, y0, y1, y2, y3, t0, t1, t2, t3, tmp;
        
        assign {a0, a1, a2, a3} = a;
        assign tmp = a0 ^ a1 ^ a2 ^ a3;
    
        galoisMult gm0(a0^a1, t0);
        galoisMult gm1(a1^a2, t1);
        galoisMult gm2(a2^a3, t2);
        galoisMult gm3(a3^a0, t3);
        
        assign y0 = a0 ^ tmp ^ t0;
        assign y1 = a1 ^ tmp ^ t1;
        assign y2 = a2 ^ tmp ^ t2;
        assign y3 = a3 ^ tmp ^ t3;
        assign y = {y0, y1, y2, y3};    
endmodule

/////////////////////////////////////////////
// galoismult
//   Multiply by x in GF(2^8) is a left shift
//   followed by an XOR if the result overflows
//   Uses irreducible polynomial x^8+x^4+x^3+x+1 = 00011011
/////////////////////////////////////////////

module galoisMult(input  logic [7:0] a,
                  output logic [7:0] y);

    logic [7:0] aShift;
    
    assign aShift = {a[6:0], 1'b0};
    assign y = a[7] ? (aShift ^ 8'b00011011) : aShift;
endmodule
