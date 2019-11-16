//
//  functions.c
//  Software-AES
//
//  Created by Akshay Trikha on 14/11/19.
//  Copyright © 2019 Akshay Trikha. All rights reserved.
//

//#include <stdio.h>
//
////    unsigned char rotateInput[] = {0xD4, 0x27, 0x11, 0xAE, 0xE0, 0xBF, 0x98, 0xF1, 0xB8, 0xB4, 0x5D, 0xE5, 0x1E, 0x41, 0x52, 0x30};
//
//// ---------- Cipher ----------
//// helper method for subBytes
//void sBox() {
//    
//}
//
//// 1. Perform subBytes non-linear byte substitution
//void subBytes() {
//    
//}
//
//// 2. Perform shiftRows cyclical shifting state's last three rows
//void shiftRows() {
//    //  state = firstByte + sixthByte + eleventhByte + sixteenthByte + fifthByte + tenthByte + fifteenthByte + fourthByte + ninthByte + fourteenthByte + thirdByte + eighthByte + thirteenthByte + secondByte + seventhByte + twelfthByte
//}
//
//// 3. Perform mixColumns switching of state's bytes
//// helper function for mixColumn written by Profesor David Harris
//// multiply by x in GF(2^8) is a left shift followed by an XOR if the result overflows
//// uses irreducible polynomial x^8+x^4+x^3+x+1 = 00011011
//void galoisMult() {
//    
//}
//
//void mixColumn() {
//    
//}
//
//void mixColumns() {
//    
//}
//// 4. Perform addRoundKey operation
//void addRoundKey() {
//    
//}
////  Key Expansion and helper methods
//void rotWord() {
//    
//}
//
//void subWord() {
//    
//}
//
//void getRcon() {
//    
//}
//
//void keyExpansion() {
//    
//}
