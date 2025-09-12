#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>

static const uint8_t substitutionBox[256] = {
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,
    0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,
    0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,
    0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,
    0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,
    0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,
    0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,
    0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,
    0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,
    0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,
    0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,
    0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,
    0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,
    0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,
    0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,
    0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,
    0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

const uint8_t roundConstant[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};

// Math funktions and layers
uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    for(int i = 0; i < 8; i++) {
        if(b & 1) p ^= a;
        bool hiBitSet = a & 0x80;
        a <<= 1;
        if(hiBitSet) a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void subByte(uint8_t state[4][4]) {
    for(int collum = 0; collum < 4; collum++) {
        for(int row = 0; row < 4; row++) {
            state[row][collum] = substitutionBox[state[row][collum]];
        }
    }
}

void shiftRows(uint8_t state[4][4]) {
    uint8_t temp; 

    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void mixedCollums(uint8_t state[4][4]) {
    for(int i = 0; i < 4; i++) {
        uint8_t temp0 = state[0][i];
        uint8_t temp1 = state[1][i];
        uint8_t temp2 = state[2][i];
        uint8_t temp3 = state[3][i];

        state[0][i] = gmul(temp0,2) ^ gmul(temp1,3) ^ temp2 ^ temp3;
        state[1][i] = temp0 ^ gmul(temp1,2) ^ gmul(temp2,3) ^ temp3;
        state[2][i] = temp0 ^ temp1 ^ gmul(temp2,2) ^ gmul(temp3,3);
        state[3][i] = gmul(temp0,3) ^ temp1 ^ temp2 ^ gmul(temp3,2);
    }
}

void addRoundKey(uint8_t state[4][4], uint8_t key[16]) {
    for(int row = 0; row < 4; ++row) {
        for(int collum = 0; collum < 4; ++collum) {
            state[row][collum] ^= key[collum*4 + row];
        }
    }
}

void expandKey(const uint8_t key[16], uint8_t roundKeys[11][16]) { //TODO: Better naming
    for(int i = 0; i < 16; i++)
        roundKeys[0][i] = key[i];

    for(int round = 1; round <= 10; round++) {
        uint8_t temp[4];
        temp[0] = roundKeys[round-1][12];
        temp[1] = roundKeys[round-1][13];
        temp[2] = roundKeys[round-1][14];
        temp[3] = roundKeys[round-1][15];

        uint8_t t = temp[0];
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = temp[3];
        temp[3] = t;

        for(int i = 0; i < 4; i++)
            temp[i] = substitutionBox[temp[i]];

        temp[0] ^= roundConstant[round-1];

        for(int i = 0; i < 4; i++)
            roundKeys[round][i] = roundKeys[round-1][i] ^ temp[i];

        for(int i = 4; i < 16; i++)
            roundKeys[round][i] = roundKeys[round-1][i] ^ roundKeys[round][i-4];
    }
}

static inline std::vector<uint8_t> generateRandomBytes(size_t n) {
    std::vector<uint8_t> randomByteList(n);
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for(size_t i = 0; i < n; ++i) {
        randomByteList[i] = static_cast<uint8_t>(dist(gen));
    }

    return randomByteList;
}

std::vector<uint8_t> pks7Padding(const  std::vector<uint8_t> &input) {
    size_t blockSize = 16;
    size_t paddingLength = blockSize - (input.size() % blockSize);

    if(paddingLength == 0) {
        paddingLength = blockSize;
    }

    std::vector<uint8_t> output = input;
    output.insert(output.end(), paddingLength, static_cast<uint8_t>(paddingLength));

    return output;
}

std::string stringToHex(const std::vector<uint8_t> byteList) {
    std::ostringstream result;
    
    result << std::hex << std::setfill('0');

    for(uint8_t byte : byteList) {
        result << std::setw(2) << static_cast<int>(byte);
    }

    return result.str();
}

// encryption funktion
std::string encryptAES(uint8_t key[16], const std::string &message) {
    std::vector<uint8_t> msgBytes(message.begin(), message.end());
    auto padded = pks7Padding(msgBytes);

    std::vector<uint8_t> iv = generateRandomBytes(16);
    std::vector<uint8_t> previousBlock = iv;

    uint8_t roundKeys[11][16];
    expandKey(key, roundKeys);

    std::vector<uint8_t> cipherText; cipherText.reserve(padded.size());

    uint8_t state[4][4];
    
    for (size_t offset = 0; offset < padded.size(); offset += 16) {
        uint8_t block[16];
        
        for (int i = 0; i < 16; ++i) {
            block[i] = padded[offset + i] ^ previousBlock[i];
        }

        for (int i = 0; i < 16; ++i) {
            state[i%4][i/4] = block[i];
        }

        addRoundKey(state, roundKeys[0]);

        for (int r = 1; r <= 10; ++r) {
            subByte(state);
            shiftRows(state);
            if (r != 10) mixedCollums(state);
            addRoundKey(state, roundKeys[r]);
        }

        uint8_t cipherBlock[16];
        for(int i = 0; i < 16; ++i) {
            cipherBlock[i] = state[i%4][i/4];
            cipherText.push_back(cipherBlock[i]);
        }

        previousBlock.assign(cipherBlock, cipherBlock + 16);
    }

    std::vector<uint8_t> output;
    output.reserve(16 + cipherText.size());
    output.insert(output.end(), iv.begin(), iv.end());
    output.insert(output.end(), cipherText.begin(), cipherText.end());

    return stringToHex(output);
}