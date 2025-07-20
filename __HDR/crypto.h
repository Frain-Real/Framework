#pragma once

#include "standard.h"
#include "aes.h"
#include "rsa.h"
#include "ecc.h"
#include "tdes.h"
#include "sha2.h"
#include "sha3.h"
#include "crc.h"

enum class crypto__crypto_type {
    AES,
    RSA,
    ECC,
    TDES,
    SHA2,
    SHA3,
    CRC
}
template <crypto__crypto_type CRYPTOTYPE>
class Crypto {
private:
    CRYPTOTYPE cr;
public:
    Crypto() : cr(){}
    ~Crypto() : ~cr(){}
#if CRYPTOTYPE == SHA2 || CRYPTOTYPE == SHA3 || CRYPTOTYPE == CRC
    bool Count() {
        cr.Count();
    }    
#else
    bool Encrypt() {
        cr.Encrypt();
    }
    bool Decrypt() {
        cr.Decrypt();
    }
#endif
};