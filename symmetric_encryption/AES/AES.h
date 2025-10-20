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
std::string generateKeyAES();
std::string encryptAES(std::string hexKey, const std::string &message);
std::string decryptAES(std::string hexKey, const std::string &encryptedMessage);

#endif