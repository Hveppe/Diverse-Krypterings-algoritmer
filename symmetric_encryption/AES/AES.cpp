#include "AES.h"

const uint8_t roundConstant[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};

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

static const uint8_t invSubstitutionBox[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,
    0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,
    0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,
    0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,
    0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,
    0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,
    0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,
    0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,
    0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,
    0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,
    0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,
    0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,
    0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,
    0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,
    0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,
    0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,
    0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};

uint8_t galoisFieldMultiplication(uint8_t a, uint8_t b) {
    uint8_t product = 0;
    for(int i = 0; i < 8; i++) {
        if(b & 1) {
            product ^= a;
        } 
        bool highBitSet = a & 0x80;
        a <<= 1;

        if(highBitSet) {
           a ^= 0x1b;
        } 

        b >>= 1;
    }
    return product;
}

// encryption layers
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
        uint8_t state0 = state[0][i];
        uint8_t state1 = state[1][i];
        uint8_t state2 = state[2][i];
        uint8_t state4 = state[3][i];

        state[0][i] = galoisFieldMultiplication(state0,2) ^ galoisFieldMultiplication(state1,3) ^ state2 ^ state4;
        state[1][i] = state0 ^ galoisFieldMultiplication(state1,2) ^ galoisFieldMultiplication(state2,3) ^ state4;
        state[2][i] = state0 ^ state1 ^ galoisFieldMultiplication(state2,2) ^ galoisFieldMultiplication(state4,3);
        state[3][i] = galoisFieldMultiplication(state0,3) ^ state1 ^ state2 ^ galoisFieldMultiplication(state4,2);
    }
}

// inverse encryption layers
void invSubBytes(uint8_t state[4][4]) {
    for(int collum = 0; collum < 4; collum++) {
        for(int row = 0; row < 4; row++) {
            state[row][collum] = invSubstitutionBox[state[row][collum]];
        }
    }
}

void invShiftRows(uint8_t state[4][4]) {
    uint8_t temp; 

    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

void invMixedCollumns(uint8_t state[4][4]) {
    for(int i = 0; i < 4; i++) {
        uint8_t state0 = state[0][i];
        uint8_t state1 = state[1][i];
        uint8_t state2 = state[2][i];
        uint8_t state3 = state[3][i];

        state[0][i] = galoisFieldMultiplication(state0, 14) ^ galoisFieldMultiplication(state1, 11) ^ galoisFieldMultiplication(state2, 13) ^ galoisFieldMultiplication(state3, 9);
        state[1][i] = galoisFieldMultiplication(state0, 9) ^ galoisFieldMultiplication(state1, 14) ^ galoisFieldMultiplication(state2, 11) ^ galoisFieldMultiplication(state3, 13);
        state[2][i] = galoisFieldMultiplication(state0, 13) ^ galoisFieldMultiplication(state1, 9) ^ galoisFieldMultiplication(state2, 14) ^ galoisFieldMultiplication(state3, 11);
        state[3][i] = galoisFieldMultiplication(state0, 11) ^ galoisFieldMultiplication(state1, 13) ^ galoisFieldMultiplication(state2, 9) ^ galoisFieldMultiplication(state3, 14);
    }
}

// key functions for both encryption and decryption
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

// padding functions
std::vector<uint8_t> pks7Padding(const std::vector<uint8_t> &input) {
    size_t blockSize = 16;
    size_t paddingLength = blockSize - (input.size() % blockSize);

    if(paddingLength == 0) {
        paddingLength = blockSize;
    }

    std::vector<uint8_t> output = input;
    output.insert(output.end(), paddingLength, static_cast<uint8_t>(paddingLength));

    return output;
}

std::vector<uint8_t> removePks7Padding(const std::vector<uint8_t> &input) {
    if(input.size() == 0) {
        return input;
    }

    uint8_t pad = input.back();

    if(pad == 0 || 16 < pad) {
        return input;
    }

    for(size_t i = input.size() - pad; i < input.size(); ++i) {
        if(input[i] != pad) {
            return input;
        }
    }

    return std::vector<uint8_t>(input.begin(), input.end() - pad);
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

// conversion betwen hex and bytes
std::string byteToHex(const std::vector<uint8_t> &bytes) {
    std::ostringstream hex;
    
    hex << std::hex << std::setfill('0');

    for(uint8_t byte : bytes) {
        hex << std::setw(2) << static_cast<int>(byte);
    }

    return hex.str();
}

std::vector<u_int8_t> hexToByte(const std::string &hex) {
    std::vector<uint8_t> bytes;
    bytes.reserve(hex.length() / 2);

    for(size_t i = 0; i < hex.length(); i += 2) {
        bytes.push_back(std::stoi(hex.substr(i, 2), nullptr, 16));
    }
    return bytes;
}

void convertKeyToBytes(uint8_t key[16], std::string hexKey) {
    std::vector<uint8_t> bytes = hexToByte(hexKey);
    for(size_t i = 0; i < bytes.size(); i++) {
        key[i] = bytes[i];
    }
}

// ----------------------------------Key Generation----------------------------------
std::string generateKeyAES() {
    std::vector<u_int8_t> key(16);
    std::random_device rd;
    for(size_t i = 0; i < 16; i++) {
        key[i] = static_cast<uint8_t>(rd());
    }
    return byteToHex(key);
}

// ---------------------Encryption and decryption functions--------------------------
std::string encryptAES(std::string hexKey, const std::string &message) {
    // convert key from hex to byte
    uint8_t key[16];
    convertKeyToBytes(key, hexKey);

    std::vector<uint8_t> msgBytes(message.begin(), message.end());
    auto padded = pks7Padding(msgBytes);

    std::vector<uint8_t> iv = generateRandomBytes(16);
    std::vector<uint8_t> previousBlock = iv;

    uint8_t roundKeys[11][16];
    expandKey(key, roundKeys);

    std::vector<uint8_t> cipherText; 
    cipherText.reserve(padded.size());

    uint8_t state[4][4];
    
    for(size_t offset = 0; offset < padded.size(); offset += 16) {
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

    return byteToHex(output);
}

std::string decryptAES(std::string hexKey, const std::string &encryptedMessage) {
    // convert key from hex to byte
    uint8_t key[16];
    convertKeyToBytes(key, hexKey);

    std::vector<u_int8_t> cipherBytes = hexToByte(encryptedMessage);

    if(cipherBytes.size() < 16) { // invalid length
        return "";
    }

    std::vector<uint8_t> iv(cipherBytes.begin(), cipherBytes.begin() + 16);
    std::vector<uint8_t> cipherText(cipherBytes.begin() + 16, cipherBytes.end());

    uint8_t roundKeys[11][16];
    expandKey(key, roundKeys);

    std::vector<uint8_t> decryptedText;
    decryptedText.reserve(cipherText.size());
    uint8_t previousBlock[16];

    std::copy(iv.begin(), iv.end(), previousBlock);

    uint8_t state[4][4];

    for(size_t offset = 0; offset < cipherText.size(); offset += 16) {
        uint8_t block[16];

        for(int i = 0; i < 16; ++i) {
            state[i%4][i/4] = cipherText[offset + i];
        }

        addRoundKey(state, roundKeys[10]);

        for(int r = 9; r >= 0; --r) {
            if(r != 9) invMixedCollumns(state);
            invShiftRows(state);
            invSubBytes(state);
            addRoundKey(state, roundKeys[r]);
        }

        uint8_t plainBlock[16];
        for(int i = 0; i < 16; ++i) {
            plainBlock[i] = state[i%4][i/4] ^ previousBlock[i];
            decryptedText.push_back(plainBlock[i]);
        }

        std::copy(cipherText.begin() + offset, cipherText.begin() + offset + 16, previousBlock);

    }

    std::vector<uint8_t> unPaddedText = removePks7Padding(decryptedText);
    return std::string(unPaddedText.begin(), unPaddedText.end());
}

