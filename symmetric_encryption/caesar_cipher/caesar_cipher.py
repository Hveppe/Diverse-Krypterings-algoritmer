chars : str = "abcdefghijklmnopqrstuvwxyz"

def encryptCeasar(message : str, key : int) -> str:
    encryptedMessage : str = ""

    for char in message:
        encryptedMessage += chars[chars.find(char.lower()) + key % 26]

    return encryptedMessage

def decryptCaesar(message : str, key : int) -> str:
    decryptedMessage : str = ""

    for char in message:
        decryptedMessage += chars[chars.find(char.lower()) - key % 26]

    return decryptedMessage

print(encryptCeasar("hello", 5))