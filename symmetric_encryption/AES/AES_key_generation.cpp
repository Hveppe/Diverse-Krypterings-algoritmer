#include "AES.h"

void generateKeyAES(uint8_t key[16]) {
    std::random_device rd;
    for(size_t i = 0; i < 16; i++) {
        key[i] = static_cast<uint8_t>(rd());
    }
}

void printKeyHexAES(uint8_t key[16]) {
     std::cout << "AES 128 bit Key: ";
    for(size_t i = 0; i < 16; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(key[i]);
    }
    std::cout << std::endl;
}