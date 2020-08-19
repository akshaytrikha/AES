//  Created by Akshay Trikha on 13/11/19.
//  Copyright © 2019 Akshay Trikha. All rights reserved.

/*
C implementation of Advanced Encryption Standard (AES) encryption algorithm with 128 bit state and cipher key
Specitification located at https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define STATE_SIZE 16
typedef uint8_t state[4][4];
struct timespec start, end;

const uint8_t sBoxNumbers[256] = {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const uint8_t Rcon[10][4] = {
    {0x01, 0x00, 0x00, 0x00}, // round 0
    {0x02, 0x00, 0x00, 0x00},
    {0x04, 0x00, 0x00, 0x00},
    {0x08, 0x00, 0x00, 0x00},
    {0x10, 0x00, 0x00, 0x00},
    {0x20, 0x00, 0x00, 0x00},
    {0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00},
    {0x1B, 0x00, 0x00, 0x00},
    {0x36, 0x00, 0x00, 0x00}  // round 9
};

// Test cases
state key = {{0x2B, 0x7E, 0x15, 0x16}, {0x28, 0xAE, 0xD2, 0xA6}, {0xAB, 0xF7, 0x15, 0x88}, {0x09, 0xCF, 0x4F, 0x3C}};

state plaintext = {{0x32, 0x43, 0xF6, 0xA8}, {0x88, 0x5A, 0x30, 0x8D}, {0x31, 0x31, 0x98, 0xA2}, {0xE0, 0x37, 0x07, 0x34}};

state expected ={{0x39, 0x25, 0x84, 0x1D}, {0x02, 0xDC, 0x09, 0xFB}, {0xDC, 0x11, 0x85, 0x97}, {0x19, 0x6A, 0x0B, 0x32}};


//---------- General helper functions ----------
void printState(state inputState) {
    // loop through rows then columns
    for (size_t i = 0; i < STATE_SIZE / 4; ++i) {
        printf("%x %x %x %x ", inputState[0][i], inputState[1][i], inputState[2][i], inputState[3][i]);
        printf("\n");
    }
    printf("\n");
}

// sets state1 = state1 ^ state2
void stateXOR(state state1, state state2) {
    // loop through rows then columns
    for (size_t i = 0; i < STATE_SIZE / 4; ++i) {
        for (size_t j = 0; j < STATE_SIZE / 4; ++j) {
            state1[i][j] ^= state2[i][j];
        }
    }
}

// sets word1 = word1 ^ word2
void wordXOR(uint8_t* word1, uint8_t* word2) {
    // loop through words
    for (size_t i = 0; i < STATE_SIZE / 4; ++i) {
        word1[i] ^= word2[i];
    }
}

// ---------- Cipher ----------
// substitutes bytes in state with bytes in sBoxNumbers
void subBytes(state inputState) {
    for (size_t i = 0; i < STATE_SIZE / 4; ++i) {
        for (size_t j = 0; j < STATE_SIZE / 4; ++j) {
            uint8_t value = 0;
            uint8_t sBoxValue = 0;
            value = inputState[i][j];
            sBoxValue = sBoxNumbers[value];
            inputState[i][j] = sBoxValue;
        }
    }
}

void shiftRows(state inputState) {
    uint8_t temp1;
    uint8_t temp2;
    // first row stays same

    // rotate second row
    temp1 = (inputState)[0][1];
    (inputState)[0][1] = (inputState)[1][1];
    (inputState)[1][1] = (inputState)[2][1];
    (inputState)[2][1] = (inputState)[3][1];
    (inputState)[3][1] = temp1;
    
    // rotate third row
    temp1 = (inputState)[0][2];
    (inputState)[0][2] = (inputState)[2][2];
    (inputState)[2][2] = temp1;
    temp1 = (inputState)[1][2];
    (inputState)[1][2] = (inputState)[3][2];
    (inputState)[3][2] = temp1;
    
    // rotate fourth row
    temp1 = (inputState)[0][3];
    (inputState)[0][3] = (inputState)[3][3];
    temp2 = (inputState)[1][3];
    (inputState)[1][3] = temp1;
    
    temp1 = (inputState)[2][3];
    (inputState)[2][3] = temp2;
    (inputState)[3][3] = temp1;
}


// helper function for mixColumns
// performs Galois field operations on bytes in a column
// taken from https://en.wikipedia.org/wiki/Rijndael_MixColumns
void gmix_columns(uint8_t* column) {
    uint8_t a[4];
    uint8_t b[4];
    uint8_t c;
    uint8_t h;
    
    /* The array 'a' is simply a copy of the input array 'r'
     * The array 'b' is each element of the array 'a' multiplied by 2
     * in Rijndael's Galois field
     * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */
    
    for (c = 0; c < 4; c++) {
        a[c] = column[c];
        /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
        h = (unsigned char)((signed char)column[c] >> 7); /* arithmetic right shift, thus shifting in either zeros or ones */
        b[c] = column[c] << 1; /* implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line */
        b[c] ^= 0x1B & h; /* Rijndael's Galois field */
        
    }
    
    column[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
    column[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
    column[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
    column[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

// performs Galois field operations on all columns in a state
void mixColumns(state inputState) {
    // get pointers
    uint8_t col1[4], col2[4], col3[4], col4[4];
    uint8_t* col1Pointer = col1;
    uint8_t* col2Pointer = col2;
    uint8_t* col3Pointer = col3;
    uint8_t* col4Pointer = col4;
    uint8_t* state1Pointer = *inputState;
    uint8_t* state2Pointer = *(inputState + 1);
    uint8_t* state3Pointer = *(inputState + 2);
    uint8_t* state4Pointer = *(inputState + 3);
    
    // copy columns into arrays
    memcpy(col1Pointer, state1Pointer, 4*sizeof(inputState[0][0]));
    memcpy(col2Pointer, state2Pointer, 4*sizeof(inputState[0][0]));
    memcpy(col3Pointer, state3Pointer, 4*sizeof(inputState[0][0]));
    memcpy(col4Pointer, state4Pointer, 4*sizeof(inputState[0][0]));
    
    // apply mix columns tranformation to each each column
    gmix_columns(col1Pointer);
    gmix_columns(col2Pointer);
    gmix_columns(col3Pointer);
    gmix_columns(col4Pointer);
    
    // copy results into state
    memcpy(state1Pointer, col1Pointer, 4*sizeof(inputState[0][0]));
    memcpy(state2Pointer, col2Pointer, 4*sizeof(inputState[0][0]));
    memcpy(state3Pointer, col3Pointer, 4*sizeof(inputState[0][0]));
    memcpy(state4Pointer, col4Pointer, 4*sizeof(inputState[0][0]));
}

// Key Expansion 1
// column [a0,a1,a2,a3] --> [a1,a2,a3,a0]
void rotateWord(uint8_t* word) {
    uint8_t a0 = word[0];
    for(size_t i = 0; i < 3; ++i) {
        word[i] = word[i+1];
    }
    word[3] = a0;
}

// Key Expansion 2
// applies S-box substitution to each byte in vector
void subWord(uint8_t* word) {
    for (size_t i = 0; i < STATE_SIZE / 4; ++i) {
        word[i] = sBoxNumbers[word[i]];
    }
}

// Key Expansion 3
// generate key for each iteration of algorithm
void keyExpansion(state inputKey, uint8_t round) {
    // save input key
    state oldKey;
    memcpy(oldKey, inputKey, 16);
    
    // get pointers
    uint8_t col1[4], col2[4], col3[4], col4[4];
    uint8_t* col1Pointer = col1;
    uint8_t* col2Pointer = col2;
    uint8_t* col3Pointer = col3;
    uint8_t* col4Pointer = col4;
    uint8_t* key1Pointer = *inputKey;
    uint8_t* key2Pointer = *(inputKey + 1);
    uint8_t* key3Pointer = *(inputKey + 2);
    uint8_t* key4Pointer = *(inputKey + 3);

    // copy key columns into arrays
    memcpy(col1Pointer, key1Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(col2Pointer, key2Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(col3Pointer, key3Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(col4Pointer, key4Pointer, 4*sizeof(inputKey[0][0]));
    
    // copy col4 into RconTemp, used for intermediate processing
    uint8_t RconTemp[4];
    memcpy(RconTemp, col4, 4);
    
    // rotate lowest column
    rotateWord(RconTemp);
    
    // S-box substitute
    subWord(RconTemp);
    
    // get round's Rcon value
    uint8_t currentRcon[4];
    memcpy(currentRcon, Rcon[round], 4);
    
    // col4 = col4 XOR currentRcon
    wordXOR(RconTemp, currentRcon);
    
    // col1 = col1 XOR col4
    wordXOR(col1, RconTemp);
    
    // col2 = col2 XOR col1
    wordXOR(col2, col1);
    
    // col3 = col3 XOR col2
    wordXOR(col3, col2);
    
    // col4 = old col4 XOR col3
    wordXOR(col4, col3);

    // copy results into key
    memcpy(key1Pointer, col1Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(key2Pointer, col2Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(key3Pointer, col3Pointer, 4*sizeof(inputKey[0][0]));
    memcpy(key4Pointer, col4Pointer, 4*sizeof(inputKey[0][0]));
}

//---------- Main ----------
int main(int argc, const char * argv[]) {
    printf("plaintext input\n");
    printState(plaintext);

    // start stopwatch
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    
    // round 1
    // plaintext = plaintext XOR first round key
    stateXOR(plaintext, key);
    
    // run 9 rounds of AES algorithm
    for (uint8_t i = 0; i < 9; ++i) {
        // perform subBytes on state
        subBytes(plaintext);
        
        // perform shiftRows on state
        shiftRows(plaintext);
        
        // perform mixColumns on state
        mixColumns(plaintext);
        
        // perform keyExpansion on key
        keyExpansion(key, i);
        
        // state = state XOR key
        stateXOR(plaintext, key);
    }
    
    // round 10
    // perform subBytes on state
    subBytes(plaintext);

    // perform shiftRows on state
    shiftRows(plaintext);
    
    // perform keyExpansion on key
    keyExpansion(key, 9);

    // state = state XOR key
    stateXOR(plaintext, key);
    
    // stop stopwatch
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    
    // combine time in seconds and nanoseconds (in case of clock wrap around)
    uint64_t delta_us = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
    
    printf("algorithm ran in %llu nanoseconds\n\n", delta_us);
    
    printf("enxrypted output\n");
    printState(plaintext);
    
    return 0;
}
