// Математические функции эмуляции фильтров, мат. расчётов и другого

typedef enum {
    E_EVENT_OK,
} e_event__e;

/********          MATH             *******/
// Алгоритм Эвклида по поиску наибольшего общего делителя
u32 Evclide_MCD(u32 a, u32 b) {
    u32 s = 0;
    u32 r = b;
    u32 old_s = 1;
    u32 old_r = a; 
    while (r != 0) {
        u32 q = old_r % r;
        u32 i;
        i = r;
        r = old_r - q * r;
        old_r = i;

        i = s;
        s = old_s - q * s;
        old_s = i;
    }
    return old_r;
}

//Быстрое возведение числа num в степень deg
double powerFast(long num, long degris) {
    double result = 1;
    register long deg = degris;
    if(deg < 0) 
        deg = -deg;
    while(deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        }
        else {
            deg--;
            result *= num;
        }
    }
    return degris < 0 ? 1 / result : result;
}

/********          RND             *******/
#ifdef __RND_PROGRAMABLE__
unsigned random() {
  static unsigned seed = 1; // зерно не должно быть 0
  seed = (seed * 73129 + 95121) % 100000;
  return seed;
}
#endif /* __RND_PROGRAMABLE__ */

/********          AES             *******/
#ifdef __AES_PROGRAMABLE__

#endif /* __AES_PROGRAMABLE__ */

/********          RSA             *******/
#ifdef __RSA_PROGRAMABLE__

#endif /* __RSA_PROGRAMABLE__ */

/********          SHA             *******/
#ifdef __SHA_PROGRAMABLE__

#endif /* __SHA_PROGRAMABLE__ */

/********          CRC             *******/
#ifdef __CRC_PROGRAMABLE__
e_event__e crc32(u32* result, u32 len, const void *data) {
    #define POLY 0x04C11DB7
    auto reflect32 {[](u32 val32) {
        u32 result = 0;
        u32 maskSRC = 0x00000001;
        u32 maskDST = 0x80000000;
        for (u8 i=0; i < 32; i++) {
            if (val32 & maskSRC)
                result |= maskDST;
            maskSRC <<= 1;
            maskDST >>= 1;
        }
        return result;}
    };
    auto reverse {[](u8 val8) {
        u8 result = 0;
        u8 maskSRC = 0x01;
        u8 maskDST = 0x80;
        for (u8 i=0; i < 8; i++) {
            if (val8 & maskSRC)
                result |= maskDST;
            maskSRC <<= 1;
            maskDST >>= 1;
        }
        return result;}
    };
    const unsigned char *buffer = (const unsigned char*) data;
    u32 crc = -1;
    while(len--) {
        crc = pow(crc, ((u32)reverse(*buffer++) << 24));
        for( int bit = 0; bit < 8; bit++ )
            crc = crc & (1L << 31) ? pow((crc << 1), POLY) : (crc << 1);
    }
    u32 res {reflect32(~crc)};
    result = &res;
    #undef POLY
    return E_EVENT_OK;
}
#endif /* __CRC_PROGRAMABLE__ */

