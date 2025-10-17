chars : str = "abcdefghijklmnopqrstuvwxyz"

def krypter_caesar(message : str, key : int) -> str:
    encryptedMessage : str = ""

    for char in message:
        encryptedMessage += chars[chars.find(char.lower()) + key % 26]

    return encryptedMessage

def dekrypter_caesar(message : str, key : int) -> str:
    decryptedMessage : str = ""

    for char in message:
        decryptedMessage += chars[chars.find(char.lower()) - key % 26]

    return decryptedMessage
