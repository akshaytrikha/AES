"""
    Python implementation of Advanced Encryption Standard (AES) encryption algorithm
    128 bit state and cipher key
    Specitification located at https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
"""

# Test cases
key         = 0x2B7E151628AED2A6ABF7158809CF4F3C
plainText   = 0x3243F6A8885A308D313198A2E0370734
expected    = 0x3925841D02DC09FBDC118597196A0B32
# key         = 0x000102030405060708090A0B0C0D0E0F
# plainText   = 0x00112233445566778899AABBCCDDEEFF
# expected    = 0x69C4E0D86A7B0430D8CDB78070B4C55A

"""General helper functions"""
# returns hex string of hex1 XOR hex2
def hexXOR(hex1, hex2):
    return hex(hex1 ^ hex2)

"""Cipher"""
# helper method for subBytes
def sBox():
    return 1

"""1. Perform subBytes non-linear byte substitution"""
def subBytes(state):
    return 1

"""2. Perform shiftRows cyclical shifting state's last three rows"""
def shiftRows(state):
    return 1

"""3. Perform mixColumns switching of state's bytes"""
def mixColumns(state):
    return 1

"""4. Perform addRoundKey operation"""
def addRoundKey(state):
    return 1

# Key Expansion and helper methods
def rotWord():
    return 1

def subWord():
    return 1

def getRcon():
    return 1

def keyExpansion():
    return 1

def main():
    print(hex(key))
    print(hexXOR(0x20, 0x10))
    return 1

if (__name__ == "__main__"):
    main()
