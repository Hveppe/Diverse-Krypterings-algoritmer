#include "caesar_cipher.h"

std::string encryptCaesar(int key, std::string message) {
    std::string encryptedMessage = "";
    int charIntValue;

    for(char letter : message) {
        charIntValue = (static_cast<int>(std::tolower(letter)) + key - 97) % 26 + 97;
        encryptedMessage.push_back(static_cast<char>(charIntValue));
    }

    return encryptedMessage;
}

std::string decryptCaesar(int key, std::string message) {
    std::string decryptedMessage = "";
     int charIntValue;

    for(char letter : message) {
        charIntValue = (static_cast<int>(std::tolower(letter)) - key - 97) % 26 + 97;
        decryptedMessage.push_back(static_cast<char>(charIntValue));
    }

    return decryptedMessage;
}
