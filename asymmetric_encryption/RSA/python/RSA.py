import hashlib

def encryptRSA(pk: tuple, sk: tuple, besked: str) -> str:
    e, n = pk
    d, n_s = sk

    Result = ""
    max_len = len(str(n))

    for item in besked:         
        Result += str(pow(ord(item), e ,n)).zfill(max_len)

    # create signatur with hash
    signatur = int(hashlib.sha256(besked.encode()).hexdigest(), 16) % n_s
    signatur = pow(signatur, d, n_s)

    return f"{Result}|{signatur}"


def decryptRSA(pk: tuple, sk: tuple, besked: str) -> str:
    e, n = pk
    d, n_s = sk
    
    Result = ""
    max_len = len(str(n))
            
    krypteret_besked, signatur = besked.split("|")
    
    for item in range(0, len(krypteret_besked), max_len):
        kryptere_tal = krypteret_besked[item: item + max_len] 
        Result += chr(pow(int(kryptere_tal), d ,n_s)) 

    # Decrypt signatur and find hash
    hash_besked = pow(int(signatur), e, n)
    valideret_hash = int(hashlib.sha256(Result.encode()).hexdigest(), 16) % n

    # validate hash
    if valideret_hash == hash_besked:
        return True, Result
    return False, Result