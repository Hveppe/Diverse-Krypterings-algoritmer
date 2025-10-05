#include "AES.h"

const uint8_t roundConstant[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};

// Math funktions and layers
uint8_t galoisFieldMultiplication(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    for(int i = 0; i < 8; i++) {
        if(b & 1) {
            p ^= a;
        } 
        bool hiBitSet = a & 0x80;
        a <<= 1;

        if(hiBitSet) {
           a ^= 0x1b;
        } 

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

        state[0][i] = galoisFieldMultiplication(temp0,2) ^ galoisFieldMultiplication(temp1,3) ^ temp2 ^ temp3;
        state[1][i] = temp0 ^ galoisFieldMultiplication(temp1,2) ^ galoisFieldMultiplication(temp2,3) ^ temp3;
        state[2][i] = temp0 ^ temp1 ^ galoisFieldMultiplication(temp2,2) ^ galoisFieldMultiplication(temp3,3);
        state[3][i] = galoisFieldMultiplication(temp0,3) ^ temp1 ^ temp2 ^ galoisFieldMultiplication(temp3,2);
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