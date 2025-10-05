import hashlib

def krypterer_RSA(pk: tuple, sk: tuple, besked: str) -> str:
    e, n = pk
    d, n_s = sk

    Result = ""
    max_len = len(str(n))

    for item in besked:         
        Result += str(pow(ord(item), e ,n)).zfill(max_len) # Kryptere besked, samt tilføjer nuller foran beskeden til den har samme længde som max_len

    # laver signatur med hash
    signatur = int(hashlib.sha256(besked.encode()).hexdigest(), 16) % n_s
    signatur = pow(signatur, d, n_s)

    return f"{Result}|{signatur}"


def dekrypter_RSA(pk: tuple, sk: tuple, besked: str) -> str:
    e, n = pk
    d, n_s = sk
    
    Result = ""
    max_len = len(str(n))
            
    krypteret_besked, signatur = besked.split("|")
    
    for item in range(0, len(krypteret_besked), max_len):
        kryptere_tal = krypteret_besked[item: item + max_len] # Finder elementerne som udgør et bogstav/tegn
        Result += chr(pow(int(kryptere_tal), d ,n_s)) # Decrypter bogstav/tegn og tilføjer til string

    # Dekryptere signatur, samt finder hash for beskeden
    hash_besked = pow(int(signatur), e, n)
    valideret_hash = int(hashlib.sha256(Result.encode()).hexdigest(), 16) % n

    # Checker om hash er valideret
    if valideret_hash == hash_besked:
        return True, Result
    return False, Result