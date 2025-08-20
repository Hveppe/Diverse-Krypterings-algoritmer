def krypter_caesar(besked: str, key: int):
    krypteret_beksed = ""

    for charecter in besked:
        krypteret_beksed += chr(ord(charecter)+key) # Krypterer beskeder med key

    return krypteret_beksed

def dekrypter_caesar(besked: str, key: int):
    dekrypteret_besked = ""

    for charecter in besked:
        dekrypteret_besked += chr(ord(charecter)-key) # Dekrypterer beskeder med key

    return dekrypteret_besked