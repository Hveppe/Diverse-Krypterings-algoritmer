#ifndef RSA_H
#define RSA_H

#include <string>
#include <iostream>

// define functions and structs for export to other files
struct keyRSA {
    long long e = 0;
    long long d = 0;
    long long n = 0;
};

keyRSA generateKeysRSA(long long p, long long q);
std::string encryptRSA(long long e, long long n, std::string message);
std::string decryptRSA(long long d, long long n, std::string message);

#endif