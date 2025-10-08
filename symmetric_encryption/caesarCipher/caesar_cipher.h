#ifndef CEASAR_CIPHER_H
#define CEASAR_CIPHER_H

#include <string>

std::string encryptCaesar(int key, std::string message);
std::string decryptCaesar(int key, std::string message);

#endif