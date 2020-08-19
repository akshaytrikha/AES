// Akshay Trikha
// MicroPs Lab 7
// 7th November, 2019

// lab7.c
// bchasnov@hmc.edu, david_harris@hmc.edu 15 October 2015
// cnorfleet@hmc.edu 31 March 2019
//
// Send data to encryption accelerator over SPI
 

////////////////////////////////////////////////
// #includes
////////////////////////////////////////////////

#include <stdio.h>
#include "SAM4S4B.h"

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

#define LOAD_PIN    29
#define DONE_PIN    30
#define SUCCESS_LED 15
#define FAIL_LED    16

// Test Case from Appendix A.1, B
char key[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
                0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

char plaintext[16] = {0x32, 0x43, 0xF6, 0xA8, 0x88, 0x5A, 0x30, 0x8D,
                      0x31, 0x31, 0x98, 0xA2, 0xE0, 0x37, 0x07, 0x34};

char ct[16] = {0x39, 0x25, 0x84, 0x1D, 0x02, 0xDC, 0x09, 0xFB,
               0xDC, 0x11, 0x85, 0x97, 0x19, 0x6A, 0x0B, 0x32};

/* 
// Another test case from Appendix C.1

char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

char plaintext[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

char ct[16] = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
               0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A};
*/

////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////

void encrypt(char*, char*, char*);
void checkAnswer(char*, char*, char*);

////////////////////////////////////////////////
// Main
////////////////////////////////////////////////

int main(void) {
  char cyphertext[16];

  samInit();
  pioInit();
  spiInit(MCK_FREQ/244000, 0, 1);
  // "clock divide" = master clock frequency / desired baud rate
  // the phase for the SPI clock is 1 and the polarity is 0

  // Load and done pins
  pioPinMode(LOAD_PIN, PIO_OUTPUT);
  pioPinMode(DONE_PIN, PIO_INPUT);
  
  // debugging LEDs
  pioPinMode(SUCCESS_LED, PIO_OUTPUT);
  pioPinMode(FAIL_LED, PIO_OUTPUT);
  pioDigitalWrite(SUCCESS_LED, 0);
  pioDigitalWrite(FAIL_LED, 0);

  // hardware accelerated encryption
  encrypt(key, plaintext, cyphertext);
  checkAnswer(key, plaintext, cyphertext);
}

////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////

void checkAnswer(char *key, char *plaintext, char *cyphertext) {
  // Compare Strings:
  char correct = 1;
  for(int i = 0; i < 16; i++) {
	  volatile int k = cyphertext[i] - ct[i];
	  if(k != 0) {
		  correct = 0;
	  }
  }
  
  if(correct) {
	pioDigitalWrite(SUCCESS_LED, 1); // Success!
  } else {
	pioDigitalWrite(FAIL_LED, 1);    // Bummer.  Test failed.
  }
}

void encrypt(char *key, char *plaintext, char *cyphertext) {
  int i;

  pioDigitalWrite(LOAD_PIN, 1);

  for(i = 0; i < 16; i++) {
    spiSendReceive(plaintext[i]);
  }

  for(i = 0; i < 16; i++) {
    spiSendReceive(key[i]);
  }

  pioDigitalWrite(LOAD_PIN, 0);

  while (!pioDigitalRead(DONE_PIN));

  for(i = 0; i < 16; i++) {
    cyphertext[i] = spiSendReceive(0);
  }
}
