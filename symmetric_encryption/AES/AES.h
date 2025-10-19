#ifndef AES_H
#define AES_H

// import libraries 
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>

// define functions for export to other files
void generateKeyAES(uint8_t key[16]);
void printKeyHexAES(uint8_t key[16]);
std::string encryptAES(uint8_t key[16], const std::string &message);
std::string decryptAES(uint8_t key[16], const std::string &encryptedMessage);

#endif