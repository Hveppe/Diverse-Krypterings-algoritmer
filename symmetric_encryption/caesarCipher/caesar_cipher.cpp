#include "caesar_cipher.h"

std::string encryptCaesar(int key, std::string message) {
    std::string encryptedMessage = "";

    for(char letter : message) {
        encryptedMessage.push_back(static_cast<char>(static_cast<int>(letter) + key));
    }

    return encryptedMessage;
}

std::string decryptCaesar(int key, std::string message) {
    std::string decryptedMessage = "";

    for(char letter : message) {
        decryptedMessage.push_back(static_cast<char>(static_cast<int>(letter) - key));
    }

    return decryptedMessage;
}