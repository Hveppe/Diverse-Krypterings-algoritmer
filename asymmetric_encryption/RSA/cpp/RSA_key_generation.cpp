#include "RSA.h"

long long gcd(long long firstNumber, long long secondNumber) {
    while(secondNumber != 0) {
        long long temp = secondNumber;
        secondNumber = firstNumber % secondNumber;
        firstNumber = temp;
    }
    return firstNumber;
}

// Technically not inverse of modulo but bruteforce of d
long long modInverse(long long e, long long phi) {
    for(long long d = 2; d < phi; d++) {
        if((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}

keyRSA generateKeysRSA(long long p, long long q) {
    keyRSA key;
    
    key.n = p * q;
    long long phi = (p - 1) * (q - 1);

    for(long long e = 2; e < phi; e++) {
        if(gcd(e, phi) == 1) {
            key.e = e;
            break;
        }
    }

    key.d = modInverse(key.e, phi);

    return key;
}
