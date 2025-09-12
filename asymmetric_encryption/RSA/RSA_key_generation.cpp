struct keyRSA{
    int e = 0;
    int d = 0;
    int n = 0;
};

int gcd(int firstNumber, int secondNumber) {
    while(secondNumber != 0) {
        int temp = secondNumber;
        secondNumber = firstNumber % secondNumber;
        firstNumber = temp;
    }
    return firstNumber;
}

int modInverse(int e, int phi) {
    for(int d = 2; d < phi; d++) {
        if((e * d) % phi == 1) {
            return d;
        }
    }
}

keyRSA generateKeys(int p, int q) {
    keyRSA key;
    
    key.n = p * q;
    int phi = (p - 1) * (q - 1);

    for(int e = 2; e < phi; e++) {
        if(gcd(e, phi) == 1) {
            key.e = e;
            break;
        }
    }

    key.d = modInverse(key.e, phi);

    return key;
}
