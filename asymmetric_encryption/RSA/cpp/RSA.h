#ifndef RSA_H
#define RSA_H

#include <string>
#include <iostream>

// define functions and structs for export to other files
struct keyRSA;
keyRSA generateKeys(long long p, long long q);
std::string EncryptRSA(long long e, long long n, std::string message);
std::string decryptRSA(long long d, long long n, std::string message);

#endif