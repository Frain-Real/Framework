#ifndef __CRYPTO__
#define __CRYPTO__

#ifndef __AES__
#define __AES__

#include <stdint.h> // Для uint8_t

// --- Константы AES ---
// S-box
static const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa1, 0xa2, 0x44, 0x80, 0x8e, 0xeb,
    0xb7, 0xcc, 0x40, 0xe0, 0x1f, 0xc2, 0x7a, 0xfd, 0x6a, 0x62, 0x0e, 0x1c, 0xf9, 0xbe, 0x78, 0xec,
    0xb4, 0xc6, 0xe8, 0xdd, 0x7e, 0xbb, 0xd6, 0xbc, 0x42, 0x02, 0x3e, 0xc1, 0xa3, 0x1a, 0xcb, 0x14,
    0x34, 0x0d, 0x93, 0x27, 0xcd, 0xa0, 0x8d, 0x0f, 0xd8, 0xe6, 0x8e, 0xc0, 0x3b, 0xd3, 0xe5, 0xb8,
    0x3c, 0x6d, 0x8c, 0x9e, 0x45, 0x70, 0x6d, 0x6a, 0x22, 0x6d, 0x6e, 0x43, 0xee, 0x74, 0x8b, 0x9d,
    0x8a, 0x60, 0xb1, 0xb2, 0x98, 0x9a, 0x9c, 0x4c, 0x4e, 0x3a, 0xef, 0x56, 0x5b, 0x2a, 0x49, 0x4a,
    0x4b, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
    0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
    0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8,
    0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
    0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8,
    0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8,
    0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

// Inverse S-box
static const uint8_t inv_sbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe5, 0xf9, 0x12, 0xe1, 0x63, 0x2d, 0x71, 0x4d,
    0x04, 0x18, 0xa0, 0x07, 0xb1, 0xba, 0x7f, 0xd2, 0x53, 0x5f, 0x26, 0x69, 0x9a, 0x0f, 0x9b, 0x6a,
    0x4d, 0x4b, 0x7f, 0x3f, 0x86, 0xd7, 0x7e, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0,
    0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0,
    0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};


// Round constants
static const uint8_t rcon[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

// --- Вспомогательные функции для работы с конечным полем GF(2^8) ---

// Умножение на 2 в GF(2^8)
// Используется для MixColumns
static inline uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t hi_bit_set;
    for (int counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) {
            p ^= a;
        }
        hi_bit_set = (uint8_t)(a & 0x80);
        a <<= 1;
        if (hi_bit_set != 0) {
            a ^= 0x1b; // x^8 + x^4 + x^3 + x + 1
        }
        b >>= 1;
    }
    return p;
}

// --- Перечисления для настройки класса AES ---
enum class AESKeySize {
    AES_128 = 128,
    AES_192 = 192,
    AES_256 = 256
};

enum class AESMode {
    ECB,
    CBC,
    CTR
};

// --- Класс AES ---
class AES {
public:
    // Конструктор
    // key: указатель на массив байт ключа
    // keySize: размер ключа (128, 192, 256 бит)
    // mode: режим работы (ECB, CBC, CTR)
    // iv: вектор инициализации для режимов CBC и CTR (должен быть 16 байт)
    AES(const uint8_t* key, AESKeySize keySize, AESMode mode, const uint8_t* iv = nullptr);

    // Шифрование данных
    // input: указатель на входные данные
    // input_len: длина входных данных в байтах
    // output: указатель на буфер для зашифрованных данных (должен быть достаточно большим)
    // output_len: указатель на переменную, куда будет записана фактическая длина зашифрованных данных (после padding'а)
    bool Encrypt(const uint8_t* input, size_t input_len, uint8_t* output, size_t* output_len);

    // Дешифрование данных
    // input: указатель на входные данные (зашифрованные)
    // input_len: длина входных данных в байтах (зашифрованных)
    // output: указатель на буфер для дешифрованных данных
    // output_len: указатель на переменную, куда будет записана фактическая длина дешифрованных данных (после удаления padding'а)
    bool Decrypt(const uint8_t* input, size_t input_len, uint8_t* output, size_t* output_len);

    // Статический метод для расчета размера буфера с padding'ом
    static size_t GetPaddedSize(size_t data_len);

private:
    uint8_t _Nk; // Количество 32-битных слов в ключе (4, 6, 8)
    uint8_t _Nr; // Количество раундов (10, 12, 14)
    uint8_t _keySizeBits; // Размер ключа в битах
    AESMode _mode; // Режим шифрования
    uint8_t _expandedKey[240]; // Максимальный размер расширенного ключа (15 раундов * 16 байт/раунд)
    uint8_t _iv[16]; // Вектор инициализации для CBC/CTR

    // Внутренние функции AES
    void KeyExpansion(const uint8_t* key);
    void AddRoundKey(uint8_t* state, const uint8_t* roundKey);
    void SubBytes(uint8_t* state);
    void InvSubBytes(uint8_t* state);
    void ShiftRows(uint8_t* state);
    void InvShiftRows(uint8_t* state);
    void MixColumns(uint8_t* state);
    void InvMixColumns(uint8_t* state);

    // Основная функция шифрования одного блока (16 байт)
    void Cipher(uint8_t* state);

    // Основная функция дешифрования одного блока (16 байт)
    void InvCipher(uint8_t* state);

    // Функции для различных режимов
    void EncryptECB(const uint8_t* input, uint8_t* output, size_t length);
    void DecryptECB(const uint8_t* input, uint8_t* output, size_t length);
    void EncryptCBC(const uint8_t* input, uint8_t* output, size_t length);
    void DecryptCBC(const uint8_t* input, uint8_t* output, size_t length);
    void EncryptCTR(const uint8_t* input, uint8_t* output, size_t length);
    void DecryptCTR(const uint8_t* input, uint8_t* output, size_t length); // CTR одинаков для шифрования и дешифрования
    
    // Функции для PKCS7 Padding
    // Добавляет PKCS7 padding к данным. Возвращает новую длину.
    // data: указатель на буфер с данными.
    // data_len: текущая длина данных.
    // max_len: максимальный размер буфера (чтобы убедиться, что есть место для padding'а).
    static size_t AddPKCS7Padding(uint8_t* data, size_t data_len, size_t max_len);

    // Удаляет PKCS7 padding из данных. Возвращает фактическую длину данных без padding'а.
    // data: указатель на буфер с данными.
    // data_len: текущая длина данных (с padding'ом).
    static size_t RemovePKCS7Padding(const uint8_t* data, size_t data_len);
};

// --- Вспомогательные функции для Key Expansion ---

// RotWord: циклический сдвиг слова влево на 1 байт
static inline void RotWord(uint8_t* word) {
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

// SubWord: применяет S-box к каждому байту слова
static inline void SubWord(uint8_t* word) {
    word[0] = sbox[word[0]];
    word[1] = sbox[word[1]];
    word[2] = sbox[word[2]];
    word[3] = sbox[word[3]];
}

// --- Реализация класса AES ---

AES::AES(const uint8_t* key, AESKeySize keySize, AESMode mode, const uint8_t* iv) {
    _keySizeBits = static_cast<uint8_t>(keySize);
    _mode = mode;

    switch (keySize) {
        case AESKeySize::AES_128:
            _Nk = 4;
            _Nr = 10;
            break;
        case AESKeySize::AES_192:
            _Nk = 6;
            _Nr = 12;
            break;
        case AESKeySize::AES_256:
            _Nk = 8;
            _Nr = 14;
            break;
        default:
            // Обработка ошибки или установка по умолчанию (например, AES-128)
            _Nk = 4;
            _Nr = 10;
            _keySizeBits = static_cast<uint8_t>(AESKeySize::AES_128);
            break;
    }

    KeyExpansion(key);

    if (iv != nullptr && (_mode == AESMode::CBC || _mode == AESMode::CTR)) {
        memcpy(_iv, iv, 16);
    } else {
        // Для режимов CBC/CTR IV должен быть предоставлен.
        // Для ECB IV не используется, можно инициализировать нулями или не трогать.
        // Здесь для безопасности и чистоты кода обнулим.
        memset(_iv, 0, 16);
    }
}

// Key Expansion (расширение ключа)
void AES::KeyExpansion(const uint8_t* key) {
    uint8_t temp[4];
    int i = 0;

    // Копируем исходный ключ в расширенный ключ
    while (i < _Nk) {
        _expandedKey[i * 4 + 0] = key[i * 4 + 0];
        _expandedKey[i * 4 + 1] = key[i * 4 + 1];
        _expandedKey[i * 4 + 2] = key[i * 4 + 2];
        _expandedKey[i * 4 + 3] = key[i * 4 + 3];
        i++;
    }

    // Генерируем оставшиеся раундовые ключи
    int j = _Nk;
    while (j < 4 * (_Nr + 1)) {
        temp[0] = _expandedKey[(j - 1) * 4 + 0];
        temp[1] = _expandedKey[(j - 1) * 4 + 1];
        temp[2] = _expandedKey[(j - 1) * 4 + 2];
        temp[3] = _expandedKey[(j - 1) * 4 + 3];

        if (j % _Nk == 0) {
            RotWord(temp);
            SubWord(temp);
            temp[0] ^= rcon[j / _Nk];
        } else if (_Nk > 6 && j % _Nk == 4) { // Для AES-256
            SubWord(temp);
        }

        _expandedKey[j * 4 + 0] = _expandedKey[(j - _Nk) * 4 + 0] ^ temp[0];
        _expandedKey[j * 4 + 1] = _expandedKey[(j - _Nk) * 4 + 1] ^ temp[1];
        _expandedKey[j * 4 + 2] = _expandedKey[(j - _Nk) * 4 + 2] ^ temp[2];
        _expandedKey[j * 4 + 3] = _expandedKey[(j - _Nk) * 4 + 3] ^ temp[3];
        j++;
    }
}

// AddRoundKey
// state: 16-байтный блок данных
// roundKey: 16-байтный раундовый ключ
void AES::AddRoundKey(uint8_t* state, const uint8_t* roundKey) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKey[i];
    }
}

// SubBytes
// state: 16-байтный блок данных
void AES::SubBytes(uint8_t* state) {
    for (int i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];
    }
}

// InvSubBytes
// state: 16-байтный блок данных
void AES::InvSubBytes(uint8_t* state) {
    for (int i = 0; i < 16; i++) {
        state[i] = inv_sbox[state[i]];
    }
}

// ShiftRows
// state: 16-байтный блок данных
void AES::ShiftRows(uint8_t* state) {
    uint8_t temp[16];

    // Row 0: no shift
    temp[0] = state[0]; temp[4] = state[4]; temp[8] = state[8]; temp[12] = state[12];

    // Row 1: 1-byte circular shift left
    temp[1] = state[5]; temp[5] = state[9]; temp[9] = state[13]; temp[13] = state[1];

    // Row 2: 2-byte circular shift left
    temp[2] = state[10]; temp[6] = state[14]; temp[10] = state[2]; temp[14] = state[6];

    // Row 3: 3-byte circular shift left
    temp[3] = state[15]; temp[7] = state[3]; temp[11] = state[7]; temp[15] = state[11];

    memcpy(state, temp, 16);
}

// InvShiftRows
// state: 16-байтный блок данных
void AES::InvShiftRows(uint8_t* state) {
    uint8_t temp[16];

    // Row 0: no shift
    temp[0] = state[0]; temp[4] = state[4]; temp[8] = state[8]; temp[12] = state[12];

    // Row 1: 1-byte circular shift right
    temp[1] = state[13]; temp[5] = state[1]; temp[9] = state[5]; temp[13] = state[9];

    // Row 2: 2-byte circular shift right
    temp[2] = state[10]; temp[6] = state[14]; temp[10] = state[2]; temp[14] = state[6];

    // Row 3: 3-byte circular shift right
    temp[3] = state[7]; temp[7] = state[11]; temp[11] = state[15]; temp[15] = state[3];

    memcpy(state, temp, 16);
}

// MixColumns
// state: 16-байтный блок данных (работает с колонками)
void AES::MixColumns(uint8_t* state) {
    for (int i = 0; i < 4; i++) {
        uint8_t s0 = state[0 + i * 4];
        uint8_t s1 = state[1 + i * 4];
        uint8_t s2 = state[2 + i * 4];
        uint8_t s3 = state[3 + i * 4];

        state[0 + i * 4] = gmul(s0, 0x02) ^ gmul(s1, 0x03) ^ gmul(s2, 0x01) ^ gmul(s3, 0x01);
        state[1 + i * 4] = gmul(s0, 0x01) ^ gmul(s1, 0x02) ^ gmul(s2, 0x03) ^ gmul(s3, 0x01);
        state[2 + i * 4] = gmul(s0, 0x01) ^ gmul(s1, 0x01) ^ gmul(s2, 0x02) ^ gmul(s3, 0x03);
        state[3 + i * 4] = gmul(s0, 0x03) ^ gmul(s1, 0x01) ^ gmul(s2, 0x01) ^ gmul(s3, 0x02);
    }
}

// InvMixColumns
// state: 16-байтный блок данных (работает с колонками)
void AES::InvMixColumns(uint8_t* state) {
    for (int i = 0; i < 4; i++) {
        uint8_t s0 = state[0 + i * 4];
        uint8_t s1 = state[1 + i * 4];
        uint8_t s2 = state[2 + i * 4];
        uint8_t s3 = state[3 + i * 4];

        state[0 + i * 4] = gmul(s0, 0x0e) ^ gmul(s1, 0x0b) ^ gmul(s2, 0x0d) ^ gmul(s3, 0x09);
        state[1 + i * 4] = gmul(s0, 0x09) ^ gmul(s1, 0x0e) ^ gmul(s2, 0x0b) ^ gmul(s3, 0x0d);
        state[2 + i * 4] = gmul(s0, 0x0d) ^ gmul(s1, 0x09) ^ gmul(s2, 0x0e) ^ gmul(s3, 0x0b);
        state[3 + i * 4] = gmul(s0, 0x0b) ^ gmul(s1, 0x0d) ^ gmul(s2, 0x09) ^ gmul(s3, 0x0e);
    }
}

// Основная функция шифрования одного блока (16 байт)
void AES::Cipher(uint8_t* state) {
    // Начальный раунд
    AddRoundKey(state, _expandedKey);

    // _Nr - 1 полных раундов
    for (int round = 1; round < _Nr; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, _expandedKey + round * 16);
    }

    // Финальный раунд (без MixColumns)
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, _expandedKey + _Nr * 16);
}

// Основная функция дешифрования одного блока (16 байт)
void AES::InvCipher(uint8_t* state) {
    // Начальный инверсный раунд (инверсный финальный раунд шифрования)
    AddRoundKey(state, _expandedKey + _Nr * 16);
    InvShiftRows(state);
    InvSubBytes(state);

    // _Nr - 1 полных инверсных раундов
    for (int round = _Nr - 1; round > 0; round--) {
        InvMixColumns(state);
        AddRoundKey(state, _expandedKey + round * 16);
        InvShiftRows(state);
        InvSubBytes(state);
    }

    // Финальный инверсный раунд (инверсный начальный раунд шифрования)
    AddRoundKey(state, _expandedKey);
}

// --- Функции для различных режимов ---

// Encrypt ECB Mode
void AES::EncryptECB(const uint8_t* input, uint8_t* output, size_t length) {
    // В режиме ECB данные шифруются блоками по 16 байт, независимо друг от друга.
    // Length должна быть кратна 16.
    for (size_t i = 0; i < length; i += 16) {
        uint8_t block[16];
        memcpy(block, input + i, 16);
        Cipher(block);
        memcpy(output + i, block, 16);
    }
}

// Decrypt ECB Mode
void AES::DecryptECB(const uint8_t* input, uint8_t* output, size_t length) {
    // В режиме ECB данные дешифруются блоками по 16 байт, независимо друг от друга.
    // Length должна быть кратна 16.
    for (size_t i = 0; i < length; i += 16) {
        uint8_t block[16];
        memcpy(block, input + i, 16);
        InvCipher(block);
        memcpy(output + i, block, 16);
    }
}

// Encrypt CBC Mode
void AES::EncryptCBC(const uint8_t* input, uint8_t* output, size_t length) {
    // В режиме CBC каждый блок шифруется с учетом предыдущего зашифрованного блока.
    // Length должна быть кратна 16.
    uint8_t prev_ciphertext_block[16];
    memcpy(prev_ciphertext_block, _iv, 16); // Начинаем с IV

    for (size_t i = 0; i < length; i += 16) {
        uint8_t current_block[16];
        memcpy(current_block, input + i, 16);

        // XOR текущего блока с предыдущим зашифрованным блоком (или IV)
        for (int k = 0; k < 16; k++) {
            current_block[k] ^= prev_ciphertext_block[k];
        }

        Cipher(current_block); // Шифруем XOR-ed блок

        memcpy(output + i, current_block, 16); // Сохраняем зашифрованный блок
        memcpy(prev_ciphertext_block, current_block, 16); // Обновляем prev_ciphertext_block
    }
}

// Decrypt CBC Mode
void AES::DecryptCBC(const uint8_t* input, uint8_t* output, size_t length) {
    // В режиме CBC дешифрование также зависит от предыдущего зашифрованного блока.
    // Length должна быть кратна 16.
    uint8_t prev_ciphertext_block[16];
    memcpy(prev_ciphertext_block, _iv, 16); // Начинаем с IV

    for (size_t i = 0; i < length; i += 16) {
        uint8_t current_ciphertext_block[16];
        memcpy(current_ciphertext_block, input + i, 16); // Текущий зашифрованный блок

        uint8_t decrypted_block[16];
        memcpy(decrypted_block, current_ciphertext_block, 16); // Копируем для дешифрования

        InvCipher(decrypted_block); // Дешифруем текущий блок

        // XOR дешифрованного блока с предыдущим зашифрованным блоком (или IV)
        for (int k = 0; k < 16; k++) {
            decrypted_block[k] ^= prev_ciphertext_block[k];
        }

        memcpy(output + i, decrypted_block, 16); // Сохраняем дешифрованный блок
        memcpy(prev_ciphertext_block, current_ciphertext_block, 16); // Обновляем prev_ciphertext_block
    }
}

// Encrypt CTR Mode (одинаков для шифрования и дешифрования)
void AES::EncryptCTR(const uint8_t* input, uint8_t* output, size_t length) {
    uint8_t counter[16];
    uint8_t encrypted_counter[16];
    memcpy(counter, _iv, 16); // Начинаем с IV, который здесь является initial counter

    for (size_t i = 0; i < length; i += 16) {
        Cipher(counter); // Шифруем текущее значение счетчика
        memcpy(encrypted_counter, counter, 16);

        // XOR входных данных с зашифрованным счетчиком
        size_t block_len = (length - i < 16) ? (length - i) : 16;
        for (size_t k = 0; k < block_len; k++) {
            output[i + k] = input[i + k] ^ encrypted_counter[k];
        }

        // Увеличиваем счетчик на 1
        for (int k = 15; k >= 0; k--) {
            if (++counter[k] != 0) {
                break;
            }
        }
    }
}

// Decrypt CTR Mode (одинаков для шифрования и дешифрования)
void AES::DecryptCTR(const uint8_t* input, uint8_t* output, size_t length) {
    // В CTR режиме шифрование и дешифрование идентичны,
    // так как это потоковый режим, основанный на XOR.
    EncryptCTR(input, output, length);
}

// --- Реализация функций PKCS7 Padding ---

// Добавляет PKCS7 padding к данным. Возвращает новую длину.
size_t AES::AddPKCS7Padding(uint8_t* data, size_t data_len, size_t max_len) {
    uint8_t padding_value = 16 - (data_len % 16); // Сколько байт нужно добавить
    if (padding_value == 0) {
        padding_value = 16; // Если блок уже полный, добавляем целый блок padding'а
    }

    size_t new_len = data_len + padding_value;

    if (new_len > max_len) {
        // Ошибка: буфер слишком мал для padding'а
        return 0; // Возвращаем 0, чтобы сигнализировать об ошибке
    }

    for (size_t i = 0; i < padding_value; ++i) {
        data[data_len + i] = padding_value;
    }

    return new_len;
}

// Удаляет PKCS7 padding из данных. Возвращает фактическую длину данных без padding'а.
size_t AES::RemovePKCS7Padding(const uint8_t* data, size_t data_len) {
    if (data_len == 0) {
        return 0; // Нечего дешифровать/удалять
    }

    uint8_t padding_value = data[data_len - 1]; // Последний байт указывает на количество padding'а

    // Проверка на корректность padding'а:
    // 1. Значение padding_value должно быть в диапазоне [1, 16].
    // 2. Все последние 'padding_value' байтов должны быть равны 'padding_value'.
    if (padding_value == 0 || padding_value > 16 || data_len < padding_value) {
        // Некорректный padding. Это может быть результатом атаки или повреждения данных.
        // В реальном приложении здесь можно выбросить исключение или вернуть ошибку.
        return 0; // Сигнализируем об ошибке
    }

    for (size_t i = 0; i < padding_value; ++i) {
        if (data[data_len - 1 - i] != padding_value) {
            // Некорректный padding
            return 0; // Сигнализируем об ошибке
        }
    }

    return data_len - padding_value;
}

// Статический метод для расчета размера буфера с padding'ом
size_t AES::GetPaddedSize(size_t data_len) {
    size_t remainder = data_len % 16;
    if (remainder == 0) {
        return data_len + 16; // Если длина кратна 16, добавляем полный блок padding'а
    } else {
        return data_len + (16 - remainder); // Добавляем до ближайшей кратности 16
    }
}

// --- Обновленные публичные методы класса AES ---

bool AES::Encrypt(const uint8_t* input, size_t input_len, uint8_t* output, size_t* output_len) {
    if (input == nullptr || output == nullptr || output_len == nullptr) {
        return false; // Некорректные указатели
    }

    if (_mode == AESMode::CTR) {
        // CTR не требует padding'а
        *output_len = input_len;
        EncryptCTR(input, output, input_len);
        return true;
    } else {
        // ECB и CBC требуют padding
        size_t padded_len = GetPaddedSize(input_len);
        if (padded_len > *output_len && *output_len != 0) { // Если output_len передан как max_size и он меньше
            return false; // Буфер вывода слишком мал
        }
        // Копируем входные данные в выходной буфер, так как padding будет добавлен на месте
        memcpy(output, input, input_len);

        // Добавляем padding
        size_t actual_padded_len = AddPKCS7Padding(output, input_len, padded_len);
        if (actual_padded_len == 0) { // Проверяем, что padding был успешно добавлен
            return false;
        }

        // Теперь output содержит данные с padding'ом, и его длина actual_padded_len
        // Вызываем соответствующий режим шифрования
        if (_mode == AESMode::ECB) {
            EncryptECB(output, output, actual_padded_len);
        } else if (_mode == AESMode::CBC) {
            EncryptCBC(output, output, actual_padded_len);
        }
        *output_len = actual_padded_len; // Возвращаем фактическую длину зашифрованных данных
        return true;
    }
}

bool AES::Decrypt(const uint8_t* input, size_t input_len, uint8_t* output, size_t* output_len) {
    if (input == nullptr || output == nullptr || output_len == nullptr) {
        return false; // Некорректные указатели
    }

    if (_mode == AESMode::CTR) {
        // CTR не требует padding'а, длина не меняется
        *output_len = input_len;
        DecryptCTR(input, output, input_len);
        return true;
    } else {
        // ECB и CBC требуют удаления padding'а
        if (input_len == 0 || input_len % 16 != 0) {
            // Зашифрованные данные должны быть кратны 16 байтам для ECB/CBC
            return false;
        }

        // Копируем входные зашифрованные данные в выходной буфер для дешифрования на месте
        memcpy(output, input, input_len);

        // Вызываем соответствующий режим дешифрования
        if (_mode == AESMode::ECB) {
            DecryptECB(output, output, input_len);
        } else if (_mode == AESMode::CBC) {
            DecryptCBC(output, output, input_len);
        }

        // Удаляем padding
        size_t actual_decrypted_len = RemovePKCS7Padding(output, input_len);
        if (actual_decrypted_len == 0) { // Проверяем, что padding был успешно удален
            return false;
        }

        *output_len = actual_decrypted_len; // Возвращаем фактическую длину дешифрованных данных без padding'а
        return true;
    }
}

#endif // __AES__

#ifndef __ECC__ 
#define __ECC__
// Максимальный размер для больших чисел (например, для 32-битного поля, это может быть 1)
// Если вы используете, например, 256-битное поле, то это будет 256/32 = 8
#define BIGINT_WORD_SIZE 1

// Класс для работы с арифметикой в конечном поле GF(p)
class FiniteFieldArithmetic {
public:
    // Модуль поля P
    uint32_t P;

    FiniteFieldArithmetic(uint32_t modulus) : P(modulus) {}

    // Сложение по модулю
    uint32_t add(uint32_t a, uint32_t b) {
        uint64_t sum = (uint64_t)a + b;
        return sum % P;
    }

    // Вычитание по модулю
    uint32_t sub(uint32_t a, uint32_t b) {
        if (a >= b) {
            return (a - b) % P;
        } else {
            return (P - (b - a)) % P;
        }
    }

    // Умножение по модулю
    uint32_t mul(uint32_t a, uint32_t b) {
        uint64_t product = (uint64_t)a * b;
        return product % P;
    }

    // Быстрое возведение в степень по модулю (a^exp % P)
    uint32_t power(uint32_t base, uint32_t exp) {
        uint32_t res = 1;
        base %= P;
        while (exp > 0) {
            if (exp % 2 == 1) { // Если exp нечетное
                res = mul(res, base);
            }
            base = mul(base, base);
            exp /= 2;
        }
        return res;
    }

    // Расширенный алгоритм Евклида для нахождения мультипликативной инверсии
    // Возвращает x такое, что (a * x) % P == 1
    uint32_t inverse(uint32_t a) {
        int32_t m = P;
        int32_t n = a;
        int32_t t = 0, q = 1;
        int32_t r = m;
        int32_t s = n;

        while (s != 0) {
            int32_t quotient = r / s;
            int32_t temp_r = r;
            int32_t temp_t = t;
            r = s;
            t = q;
            s = temp_r - quotient * s;
            q = temp_t - quotient * q;
        }
        if (r > 1) return 0; // Инверсия не существует
        if (t < 0) t = t + m; // Приводим к положительному значению

        return (uint32_t)t;
    }

    // Структура для представления точки на эллиптической кривой
struct Point {
    uint32_t x;
    uint32_t y;
    bool isInfinity; // Флаг, указывающий, является ли точка "точкой на бесконечности"

    // Конструктор для обычной точки
    Point(uint32_t val_x = 0, uint32_t val_y = 0) : x(val_x), y(val_y), isInfinity(false) {}

    // Конструктор для точки на бесконечности
    static Point infinity() {
        Point p;
        p.isInfinity = true;
        return p;
    }

    bool operator==(const Point& other) const {
        if (isInfinity && other.isInfinity) return true;
        if (isInfinity != other.isInfinity) return false;
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Класс для работы с эллиптическими кривыми
class ECC {
public:
    uint32_t P; // Модуль поля
    uint32_t A; // Коэффициент A кривой y^2 = x^3 + Ax + B (mod P)
    uint32_t B; // Коэффициент B кривой y^2 = x^3 + Ax + B (mod P)
    Point G;    // Базовая точка (генератор) кривой
    uint32_t N; // Порядок базовой точки G (наименьшее целое N > 0 такое, что N*G = O (точка на бесконечности))

    FiniteFieldArithmetic ff;

    ECC(uint32_t modulus, uint32_t coeffA, uint32_t coeffB,
        Point generator, uint32_t orderOfG)
        : P(modulus), A(coeffA), B(coeffB), G(generator), N(orderOfG), ff(modulus)
    {
        // Проверка условия 4A^3 + 27B^2 != 0 (mod P)
        uint32_t term1 = ff.mul(ff.mul(ff.power(A, 3), 4), 1); // 4 * A^3
        uint32_t term2 = ff.mul(ff.mul(ff.power(B, 2), 27), 1); // 27 * B^2
        uint32_t discriminant = ff.add(term1, term2);

        if (discriminant == 0) {
            // В реальном приложении здесь нужно выдать ошибку или исключение
            // Для микроконтроллера можно просто зависнуть или войти в бесконечный цикл
            // или использовать assert
            // Для простоты примера, мы просто выведем сообщение, но это не безопасно.
            // Вместо этого нужно убедиться, что используемые параметры кривой корректны.
            // printf("Error: Curve parameters are invalid (4A^3 + 27B^2 == 0 mod P)\n");
        }
    }

    // Проверка, лежит ли точка на кривой
    bool isOnCurve(const Point& p) {
        if (p.isInfinity) return true;
        uint32_t lhs = ff.mul(p.y, p.y); // y^2
        uint32_t rhs = ff.add(ff.add(ff.mul(ff.mul(p.x, p.x), p.x), ff.mul(A, p.x)), B); // x^3 + Ax + B
        return lhs == rhs;
    }

    // Сложение двух точек P1 и P2
    Point addPoints(const Point& p1, const Point& p2) {
        if (p1.isInfinity) return p2;
        if (p2.isInfinity) return p1;

        // Если P1 == -P2, то P1 + P2 = O (точка на бесконечности)
        // То есть P1.x == P2.x и P1.y == P - P2.y
        if (p1.x == p2.x && ff.add(p1.y, p2.y) == 0) {
            return Point::infinity();
        }

        uint32_t lambda;
        if (p1.x == p2.x && p1.y == p2.y) { // Удвоение точки P1 == P2
            // lambda = (3x^2 + A) * (2y)^-1 (mod P)
            uint32_t three_x_squared = ff.mul(ff.mul(p1.x, p1.x), 3);
            uint32_t numerator = ff.add(three_x_squared, A);
            uint32_t two_y_inv = ff.inverse(ff.mul(2, p1.y));
            lambda = ff.mul(numerator, two_y_inv);
        } else { // Сложение разных точек
            // lambda = (y2 - y1) * (x2 - x1)^-1 (mod P)
            uint32_t numerator = ff.sub(p2.y, p1.y);
            uint32_t denominator_inv = ff.inverse(ff.sub(p2.x, p1.x));
            lambda = ff.mul(numerator, denominator_inv);
        }

        uint32_t x3 = ff.sub(ff.sub(ff.mul(lambda, lambda), p1.x), p2.x);
        uint32_t y3 = ff.sub(ff.mul(lambda, ff.sub(p1.x, x3)), p1.y);

        return Point(x3, y3);
    }

    // Умножение точки на скаляр (k * P)
    Point scalarMultiply(uint32_t k, const Point& p) {
        Point result = Point::infinity(); // Инициализируем результатом как точка на бесконечности
        Point current = p;

        while (k > 0) {
            if (k & 1) { // Если младший бит k равен 1
                result = addPoints(result, current);
            }
            current = addPoints(current, current); // Удваиваем current (current = 2 * current)
            k >>= 1; // Сдвигаем k вправо на 1 бит (делим на 2)
        }
        return result;
    }

    // Генерация случайного закрытого ключа (для примера, используем rand(), в реальной системе нужен CSPRNG)
    uint32_t generatePrivateKey() {
        // Закрытый ключ должен быть в диапазоне [1, N-1]
        // Для микроконтроллера, где нет хорошего RNG, это проблема.
        // Здесь используется rand() из cstdlib, что НЕБЕЗОПАСНО для криптографии.
        // Вам нужно будет реализовать или использовать аппаратный генератор случайных чисел.
        return (rand() % (N - 1)) + 1;
    }

    // Вычисление открытого ключа из закрытого
    Point getPublicKey(uint32_t privateKey) {
        return scalarMultiply(privateKey, G);
    }

    // Вычисление общего секрета ECDH
    Point calculateSharedSecret(uint32_t privateKey, const Point& publicKeyOther) {
        // S = privateKey * publicKeyOther
        return scalarMultiply(privateKey, publicKeyOther);
    }
};

};
#endif /* __ECC__ */

#ifndef __RSA__
#define __RSA__
#include <random>
#include <chrono>
class RSA {
public:
    // Конструктор
    RSA() : n(0), e(0), d(0) {
        // Инициализация генератора случайных чисел один раз
        rng_prime.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        rng_e.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count() + 1); // Добавляем смещение для другого сида
    }

    // Метод для генерации ключей
    void generateKeys(long long min_prime_val, long long max_prime_val) {
        long long p, q;
        do {
            p = generatePrime(min_prime_val, max_prime_val);
            q = generatePrime(min_prime_val, max_prime_val);
        } while (p == q); // Убеждаемся, что p и q различны

        n = p * q;
        long long phi = (p - 1) * (q - 1);

        e = 65537; // Общепринятое значение для e.
        // Проверяем, что e взаимно просто с phi и 1 < e < phi
        while (e >= phi || gcd(e, phi) != 1) {
            // Если 65537 не подходит, генерируем другое e в диапазоне [2, phi-1]
            std::uniform_int_distribution<long long> dist_e(2, phi - 1);
            e = dist_e(rng_e);
        }
        
        d = modInverse(e, phi);
    }

    // Метод для шифрования сообщения
    long long encrypt(long long message) const {
        return power(message, e, n);
    }

    // Метод для дешифрования сообщения
    long long decrypt(long long encrypted_message) const {
        return power(encrypted_message, d, n);
    }

    // Геттеры для ключей (для вывода и отладки)
    long long getN() const { return n; }
    long long getE() const { return e; }
    long long getD() const { return d; }

private:
    long long n; // Модуль (общая часть для открытого и закрытого ключа)
    long long e; // Открытая экспонента
    long long d; // Закрытая экспонента

    // Генераторы случайных чисел, члены класса для инициализации один раз
    std::mt19937_64 rng_prime; // Для генерации простых чисел
    std::mt19937_64 rng_e;     // Для генерации e

    // 1. Наибольший общий делитель (GCD)
    long long gcd(long long a, long long b) const {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    // 2. Модульное возведение в степень (Modular Exponentiation)
    long long power(long long base, long long exp, long long mod) const {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    // 3. Расширенный алгоритм Евклида для нахождения модульного обратного
    long long modInverse(long long a, long long m) const {
        long long m0 = m;
        long long y = 0, x = 1;

        if (m == 1) return 0;

        while (a > 1) {
            long long q = a / m;
            long long t = m;

            m = a % m, a = t;
            t = y;

            y = x - q * y;
            x = t;
        }

        if (x < 0) x += m0;
        return x;
    }

    // 4. Тест Миллера-Рабина для проверки на простоту
    bool isPrime(long long n, int k = 5) const {
        if (n <= 1 || n == 4) return false;
        if (n <= 3) return true;

        long long d = n - 1;
        while (d % 2 == 0) {
            d /= 2;
        }

        std::uniform_int_distribution<long long> dist(2, n - 2);

        for (int i = 0; i < k; ++i) {
            long long a = dist(rng_prime); 
            long long x = power(a, d, n);

            if (x == 1 || x == n - 1) continue;

            while (d != n - 1) {
                x = (x * x) % n;
                d *= 2;

                if (x == 1) return false;
                if (x == n - 1) break;
            }
            if (x != n - 1) return false;
        }
        return true;
    }

    // 5. Генерация случайного простого числа
    long long generatePrime(long long min_val, long long max_val) {
        std::uniform_int_distribution<long long> dist(min_val, max_val);
        long long p;
        do {
            p = dist(rng_prime);
            if (p % 2 == 0 && p != 2) p++; // Убедимся, что число нечетное, если не 2
        } while (!isPrime(p));
        return p;
    }
};
#endif /* __RSA__ */

#ifndef __TDES__
#define __TDES__

// Класс для TDES шифрования
class TDES {
public:
    // Конструктор: принимает три 64-битных ключа (56 эффективных бит каждый)
    TDES(const uint8_t key1[8], const uint8_t key2[8], const uint8_t key3[8]);

    // Перечисление для режимов работы
    enum class Mode {
        ECB, // Electronic Codebook
        CBC, // Cipher Block Chaining
        CTR  // Counter Mode
    };

    // Шифрование данных с padding'ом
    // input: указатель на входные данные
    // inputLen: длина входных данных в байтах
    // output: буфер для зашифрованных данных (должен быть достаточно большим)
    //         Максимальный размер: inputLen + BLOCK_SIZE
    // mode: режим работы
    // ivOrNonce: вектор инициализации (для CBC) или начальный счетчик (для CTR).
    //            Для ECB не используется (можно передать nullptr).
    //            Должен быть BLOCK_SIZE байт.
    // Возвращает фактическую длину зашифрованных данных.
    size_t encrypt(const uint8_t* input, size_t inputLen, uint8_t* output, Mode mode, const uint8_t ivOrNonce[8] = nullptr);

    // Дешифрование данных
    // input: указатель на зашифрованные данные
    // inputLen: длина зашифрованных данных в байтах (должна быть кратна BLOCK_SIZE)
    // output: буфер для дешифрованных данных (должен быть достаточно большим)
    //         Максимальный размер: inputLen
    // mode: режим работы (должен совпадать с тем, что использовался при шифровании)
    // ivOrNonce: вектор инициализации (для CBC) или начальный счетчик (для CTR).
    //            Для ECB не используется (можно передать nullptr).
    //            Должен быть BLOCK_SIZE байт.
    // Возвращает фактическую длину дешифрованных данных (без padding'а).
    size_t decrypt(const uint8_t* input, size_t inputLen, uint8_t* output, Mode mode, const uint8_t ivOrNonce[8] = nullptr);

private:
    // --- Внутренний класс для DES шифрования (без изменений) ---
    class DES {
    public:
        DES(const uint8_t key[8]);
        void encryptBlock(uint8_t data[8]);
        void decryptBlock(uint8_t data[8]);
    private:
        uint64_t subkeys[16];
        void generateSubkeys(const uint8_t key[8]);
        uint32_t feistelFunction(uint32_t rightHalf, uint64_t subkey);
        uint64_t permute(uint64_t input, const uint8_t* permutationTable, int inputBits, int outputBits);
        void rotateLeft(uint32_t* value, int bits);

        // DES-таблицы (как статические константы)
        static const uint8_t PC1[56];
        static const uint8_t PC2[48];
        static const uint8_t ShiftBits[16];
        static const uint8_t IP[64];
        static const uint8_t FP[64];
        static const uint8_t E_Permutation[48];
        static const uint8_t P_Permutation[32];
        static const uint8_t S_Boxes[8][64];
    };

    DES des1; // Первый DES
    DES des2; // Второй DES
    DES des3; // Третий DES

    // Вспомогательные методы для TDES (блочные операции)
    void tdesEncryptBlock(uint8_t data[8]);
    void tdesDecryptBlock(uint8_t data[8]);

    // Функции padding'а
    // Добавляет PKCS#7 padding к буферу.
    // data: буфер для данных.
    // currentLen: текущая длина данных в буфере.
    // Возвращает новую длину данных после добавления padding'а.
    size_t addPKCS7Padding(uint8_t* data, size_t currentLen);

    // Удаляет PKCS#7 padding из буфера.
    // data: буфер для данных.
    // currentLen: текущая длина данных в буфере (должна быть кратна BLOCK_SIZE).
    // Возвращает новую длину данных после удаления padding'а.
    size_t removePKCS7Padding(uint8_t* data, size_t currentLen);

    // Вспомогательный буфер для операций с блоками
    uint8_t blockBuffer[BLOCK_SIZE];
    uint8_t ivBuffer[BLOCK_SIZE]; // Для хранения IV/Counter
    uint8_t counterBuffer[BLOCK_SIZE]; // Для CTR режима
};

// ====================================================================================================
// Реализация DES-таблиц (размещаем их вне класса, чтобы они были статическими)
// ====================================================================================================

// Initial Permutation (IP) table
const uint8_t TDES::DES::IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation (FP) table (inverse of IP)
const uint8_t TDES::DES::FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Permuted Choice 1 (PC1) table
const uint8_t TDES::DES::PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};

// Permuted Choice 2 (PC2) table
const uint8_t TDES::DES::PC2[48] = {
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Left shifts for key schedule
const uint8_t TDES::DES::ShiftBits[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

// Expansion Permutation (E-Permutation) table
const uint8_t TDES::DES::E_Permutation[48] = {
    32, 1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9,  10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// P-Box Permutation (P-Permutation) table
const uint8_t TDES::DES::P_Permutation[32] = {
    16, 7,  20, 21,
    29, 12, 28, 17,
    1,  15, 23, 26,
    5,  18, 31, 10,
    2,  8,  24, 14,
    32, 27, 3,  9,
    19, 13, 30, 6,
    22, 11, 4,  25
};

// S-Boxes (8 S-Boxes, each 6x4 to 4 bits)
const uint8_t TDES::DES::S_Boxes[8][64] = {
    // S1
    {14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7,
     0,  15, 7,  4,  14, 2,  13, 1,  10, 6,  12, 11, 9,  5,  3,  8,
     4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
     15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0,  6,  13},
    // S2
    {15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10,
     3,  13, 4,  7,  15, 2,  8,  14, 12, 0,  1,  10, 6,  9,  11, 5,
     0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15,
     13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5,  14, 9},
    // S3
    {10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
     13, 7,  0,  9,  3,  4,  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,
     13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
     1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5,  2,  12},
    // S4
    {7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
     13, 8,  11, 5,  6,  15, 0,  3,  4,  7,  2,  12, 1,  10, 14, 9,
     10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
     3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7,  2,  14},
    // S5
    {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
     14, 11, 2,  12, 4,  7,  13, 1,  5,  0,  15, 10, 3,  9,  8,  6,
     4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
     11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4,  5,  3},
    // S6
    {12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
     10, 15, 4,  2,  7,  12, 9,  5,  6,  1,  13, 14, 0,  11, 3,  8,
     9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
     4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8,  13},
    // S7
    {4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
     13, 0,  11, 7,  4,  9,  1,  10, 14, 3,  5,  12, 2,  15, 8,  6,
     1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
     6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2,  3,  12},
    // S8
    {13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
     1,  15, 13, 8,  10, 3,  7,  4,  12, 5,  6,  11, 0,  14, 9,  2,
     7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
     2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5,  6,  11}
};

// ====================================================================================================
// Реализация методов класса DES (вспомогательного для TDES)
// ====================================================================================================

// Вспомогательная функция для перестановки битов
// input: входное 64-битное значение
// permutationTable: таблица перестановок
// inputBits: количество бит во входном значении (например, 64 для данных, 56 для ключа)
// outputBits: количество бит в выходном значении
uint64_t TDES::DES::permute(uint64_t input, const uint8_t* permutationTable, int inputBits, int outputBits) {
    uint64_t output = 0;
    for (int i = 0; i < outputBits; ++i) {
        // Получаем позицию бита из таблицы перестановок (таблицы основаны на 1, поэтому -1)
        int bitPos = permutationTable[i] - 1;
        // Проверяем, установлен ли бит во входном значении
        if ((input >> (inputBits - 1 - bitPos)) & 1) {
            // Устанавливаем бит в выходном значении
            output |= (1ULL << (outputBits - 1 - i));
        }
    }
    return output;
}

// Вспомогательная функция для циклического сдвига влево (для генерации ключей)
void TDES::DES::rotateLeft(uint32_t* value, int bits) {
    *value = (*value << bits) | (*value >> (28 - bits)); // 28 - т.к. 56-битный ключ делится на две 28-битные части
    *value &= 0x0FFFFFFF; // Обрезаем до 28 бит
}

// Генерация 16 раундовых ключей
void TDES::DES::generateSubkeys(const uint8_t key[8]) {
    uint64_t initialKey = 0;
    // Преобразуем 8 байт ключа в 64-битное значение
    for (int i = 0; i < 8; ++i) {
        initialKey = (initialKey << 8) | key[i];
    }

    // Применяем PC1 для получения 56-битного ключа
    uint64_t permutedKey = permute(initialKey, PC1, 64, 56);

    // Разделяем на две 28-битные половины C0 и D0
    uint32_t C = (uint32_t)((permutedKey >> 28) & 0x0FFFFFFF);
    uint32_t D = (uint32_t)(permutedKey & 0x0FFFFFFF);

    for (int i = 0; i < 16; ++i) {
        // Выполняем циклический сдвиг
        rotateLeft(&C, ShiftBits[i]);
        rotateLeft(&D, ShiftBits[i]);

        // Объединяем C и D, затем применяем PC2 для получения 48-битного раундового ключа
        uint64_t CD_combined = ((uint64_t)C << 28) | D;
        subkeys[i] = permute(CD_combined, PC2, 56, 48);
    }
}

// Функция Feistel (F-функция)
uint32_t TDES::DES::feistelFunction(uint32_t rightHalf, uint64_t subkey) {
    // 1. Расширение R до 48 бит (E-Permutation)
    uint64_t expandedR = permute(rightHalf, E_Permutation, 32, 48);

    // 2. XOR с раундовым ключом
    uint64_t xorResult = expandedR ^ subkey;

    // 3. Пропускаем через S-блоки
    uint32_t sboxOutput = 0;
    for (int i = 0; i < 8; ++i) {
        // Извлекаем 6 бит для текущего S-блока
        uint8_t sixBits = (uint8_t)((xorResult >> (48 - (i + 1) * 6)) & 0x3F); // 0x3F = 111111b

        // Определяем строку и столбец для S-блока
        uint8_t row = (sixBits & 0x20) >> 4 | (sixBits & 0x01); // Бит 0 и Бит 5
        uint8_t col = (sixBits >> 1) & 0x0F; // Биты 1-4

        // Получаем значение из S-блока
        uint8_t sboxValue = S_Boxes[i][row * 16 + col]; // S-блоки 4x16

        // Добавляем значение в выход
        sboxOutput = (sboxOutput << 4) | sboxValue;
    }

    // 4. Пропускаем через P-перестановку
    return (uint32_t)permute(sboxOutput, P_Permutation, 32, 32);
}

// Конструктор DES
TDES::DES::DES(const uint8_t key[8]) {
    generateSubkeys(key);
}

// Шифрование DES-блока
void TDES::DES::encryptBlock(uint8_t data[8]) {
    uint64_t block = 0;
    for (int i = 0; i < 8; ++i) {
        block = (block << 8) | data[i];
    }

    // Начальная перестановка
    block = permute(block, IP, 64, 64);

    // Разделяем на левую и правую половины
    uint32_t L = (uint32_t)(block >> 32);
    uint32_t R = (uint32_t)(block & 0xFFFFFFFF);

    // 16 раундов
    for (int i = 0; i < 16; ++i) {
        uint32_t tempL = R;
        R = L ^ feistelFunction(R, subkeys[i]);
        L = tempL;
    }

    // Объединяем L и R (поменяем местами L и R после последнего раунда)
    uint64_t combined = ((uint64_t)R << 32) | L; // Обрати внимание, L и R меняются местами на выходе

    // Конечная перестановка
    block = permute(combined, FP, 64, 64);

    // Копируем результат обратно в массив байт
    for (int i = 7; i >= 0; --i) {
        data[i] = (uint8_t)(block & 0xFF);
        block >>= 8;
    }
}

// Дешифрование DES-блока
void TDES::DES::decryptBlock(uint8_t data[8]) {
    uint64_t block = 0;
    for (int i = 0; i < 8; ++i) {
        block = (block << 8) | data[i];
    }

    // Начальная перестановка
    block = permute(block, IP, 64, 64);

    // Разделяем на левую и правую половины
    uint32_t L = (uint32_t)(block >> 32);
    uint32_t R = (uint32_t)(block & 0xFFFFFFFF);

    // 16 раундов в обратном порядке (используем ключи с конца к началу)
    for (int i = 15; i >= 0; --i) {
        uint32_t tempL = R;
        R = L ^ feistelFunction(R, subkeys[i]);
        L = tempL;
    }

    // Объединяем L и R (поменяем местами L и R после последнего раунда)
    uint64_t combined = ((uint64_t)R << 32) | L; // Обрати внимание, L и R меняются местами на выходе

    // Конечная перестановка
    block = permute(combined, FP, 64, 64);

    // Копируем результат обратно в массив байт
    for (int i = 7; i >= 0; --i) {
        data[i] = (uint8_t)(block & 0xFF);
        block >>= 8;
    }
}

// ====================================================================================================
// Реализация методов класса TDES (обновлено для режимов работы и padding'а)
// ====================================================================================================

// Конструктор TDES
TDES::TDES(const uint8_t key1[8], const uint8_t key2[8], const uint8_t key3[8])
    : des1(key1), des2(key2), des3(key3) {
    // Инициализация буферов нулями
    memset(blockBuffer, 0, BLOCK_SIZE);
    memset(ivBuffer, 0, BLOCK_SIZE);
    memset(counterBuffer, 0, BLOCK_SIZE);
}

// Вспомогательная функция TDES шифрования одного блока (EDE)
void TDES::tdesEncryptBlock(uint8_t data[8]) {
    des1.encryptBlock(data);
    des2.decryptBlock(data);
    des3.encryptBlock(data);
}

// Вспомогательная функция TDES дешифрования одного блока (DED)
void TDES::tdesDecryptBlock(uint8_t data[8]) {
    des3.decryptBlock(data);
    des2.encryptBlock(data);
    des1.decryptBlock(data);
}

// --- Padding Functions ---

size_t TDES::addPKCS7Padding(uint8_t* data, size_t currentLen) {
    size_t paddingBytes = BLOCK_SIZE - (currentLen % BLOCK_SIZE);
    if (paddingBytes == 0) { // Если данные уже кратны BLOCK_SIZE, добавляем целый блок
        paddingBytes = BLOCK_SIZE;
    }
    for (size_t i = 0; i < paddingBytes; ++i) {
        data[currentLen + i] = (uint8_t)paddingBytes;
    }
    return currentLen + paddingBytes;
}

size_t TDES::removePKCS7Padding(uint8_t* data, size_t currentLen) {
    if (currentLen == 0 || currentLen % BLOCK_SIZE != 0) {
        // Ошибка: неверная длина данных для удаления padding'а
        return 0; // Или бросить исключение
    }
    uint8_t paddingBytes = data[currentLen - 1];
    if (paddingBytes == 0 || paddingBytes > BLOCK_SIZE) {
        // Ошибка: неверное значение padding'а
        return 0; // Или бросить исключение
    }
    // Проверяем, что все padding-байты имеют правильное значение
    for (size_t i = 0; i < paddingBytes; ++i) {
        if (data[currentLen - 1 - i] != paddingBytes) {
            // Ошибка: невалидный padding
            return 0; // Или бросить исключение
        }
    }
    return currentLen - paddingBytes;
}

// --- Main Encryption/Decryption Methods ---

size_t TDES::encrypt(const uint8_t* input, size_t inputLen, uint8_t* output, Mode mode, const uint8_t ivOrNonce[8]) {
    size_t paddedLen = inputLen + (BLOCK_SIZE - (inputLen % BLOCK_SIZE));
    if (inputLen % BLOCK_SIZE == 0) {
        paddedLen = inputLen + BLOCK_SIZE; // PKCS#7: если кратно, добавляем целый блок
    }

    // Проверка на размер выходного буфера, если MAX_DATA_SIZE не определен
    // Для микроконтроллеров обычно предполагается, что буферы заданы статически
    // и достаточно велики, или же передаются явно вызывающей стороной.
    // Если MAX_DATA_SIZE определен, убедимся, что inputLen не превышает лимит.
    if (inputLen > MAX_DATA_SIZE) {
        // Ошибка: входные данные слишком велики для буфера
        return 0;
    }

    // Копируем входные данные во временный буфер и добавляем padding
    uint8_t tempBuffer[MAX_DATA_SIZE + BLOCK_SIZE]; // Достаточно большой для данных + padding
    memcpy(tempBuffer, input, inputLen);
    paddedLen = addPKCS7Padding(tempBuffer, inputLen);

    size_t numBlocks = paddedLen / BLOCK_SIZE;
    size_t currentOffset = 0;

    if (ivOrNonce) {
        memcpy(ivBuffer, ivOrNonce, BLOCK_SIZE); // Копируем IV/Nonce
        memcpy(counterBuffer, ivOrNonce, BLOCK_SIZE); // Для CTR, копируем начальный счетчик
    } else if (mode != Mode::ECB) {
        // Если IV/Nonce не передан, а режим требует его, это ошибка
        return 0; // Или можно сгенерировать случайный IV, но это не для МК обычно
    }

    for (size_t i = 0; i < numBlocks; ++i) {
        memcpy(blockBuffer, tempBuffer + currentOffset, BLOCK_SIZE); // Копируем текущий блок

        switch (mode) {
            case Mode::ECB:
                tdesEncryptBlock(blockBuffer);
                break;
            case Mode::CBC:
                // XOR с предыдущим зашифрованным блоком (или IV для первого)
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    blockBuffer[j] ^= ivBuffer[j];
                }
                tdesEncryptBlock(blockBuffer);
                memcpy(ivBuffer, blockBuffer, BLOCK_SIZE); // Обновляем IV
                break;
            case Mode::CTR:
                // Шифруем счетчик
                tdesEncryptBlock(counterBuffer);
                // XOR с открытым текстом
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    blockBuffer[j] ^= counterBuffer[j];
                }
                // Увеличиваем счетчик
                // Простая инкрементация (возможны более сложные для больших счетчиков)
                for (int j = BLOCK_SIZE - 1; j >= 0; --j) {
                    if (++ivBuffer[j] != 0) break;
                }
                memcpy(counterBuffer, ivBuffer, BLOCK_SIZE); // Обновляем счетчик для следующего раунда
                break;
        }
        memcpy(output + currentOffset, blockBuffer, BLOCK_SIZE); // Копируем результат
        currentOffset += BLOCK_SIZE;
    }
    return paddedLen;
}

size_t TDES::decrypt(const uint8_t* input, size_t inputLen, uint8_t* output, Mode mode, const uint8_t ivOrNonce[8]) {
    if (inputLen == 0 || inputLen % BLOCK_SIZE != 0) {
        // Ошибка: длина входных данных должна быть кратна размеру блока
        return 0;
    }

    // Проверка на размер входного буфера, если MAX_DATA_SIZE не определен
    if (inputLen > MAX_DATA_SIZE + BLOCK_SIZE) { // MAX_DATA_SIZE + BLOCK_SIZE для учёта padding'а
        // Ошибка: входные данные слишком велики для буфера
        return 0;
    }

    size_t numBlocks = inputLen / BLOCK_SIZE;
    size_t currentOffset = 0;

    // Временный буфер для дешифрованных данных (перед удалением padding'а)
    uint8_t tempDecryptedBuffer[MAX_DATA_SIZE + BLOCK_SIZE];

    if (ivOrNonce) {
        memcpy(ivBuffer, ivOrNonce, BLOCK_SIZE); // Копируем IV/Nonce
        memcpy(counterBuffer, ivOrNonce, BLOCK_SIZE); // Для CTR, копируем начальный счетчик
    } else if (mode != Mode::ECB) {
        return 0; // Ошибка: IV/Nonce не передан
    }

    for (size_t i = 0; i < numBlocks; ++i) {
        memcpy(blockBuffer, input + currentOffset, BLOCK_SIZE); // Копируем текущий блок

        switch (mode) {
            case Mode::ECB:
                tdesDecryptBlock(blockBuffer);
                break;
            case Mode::CBC: {
                uint8_t tempBlock[BLOCK_SIZE]; // Сохраняем текущий зашифрованный блок
                memcpy(tempBlock, blockBuffer, BLOCK_SIZE);
                tdesDecryptBlock(blockBuffer);
                // XOR с предыдущим зашифрованным блоком (или IV для первого)
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    blockBuffer[j] ^= ivBuffer[j];
                }
                memcpy(ivBuffer, tempBlock, BLOCK_SIZE); // Обновляем IV
                break;
            }
            case Mode::CTR:
                // Шифруем счетчик (то же, что и при шифровании)
                tdesEncryptBlock(counterBuffer);
                // XOR с зашифрованным текстом
                for (int j = 0; j < BLOCK_SIZE; ++j) {
                    blockBuffer[j] ^= counterBuffer[j];
                }
                // Увеличиваем счетчик
                for (int j = BLOCK_SIZE - 1; j >= 0; --j) {
                    if (++ivBuffer[j] != 0) break;
                }
                memcpy(counterBuffer, ivBuffer, BLOCK_SIZE); // Обновляем счетчик для следующего раунда
                break;
        }
        memcpy(tempDecryptedBuffer + currentOffset, blockBuffer, BLOCK_SIZE); // Копируем результат
        currentOffset += BLOCK_SIZE;
    }

    // Удаляем padding после дешифрования
    size_t finalLen = removePKCS7Padding(tempDecryptedBuffer, currentOffset);
    if (finalLen == 0 && inputLen > 0) { // Если padding был некорректен
        return 0;
    }
    memcpy(output, tempDecryptedBuffer, finalLen); // Копируем окончательные данные
    return finalLen;
}

#endif /* __TDES__ */

#ifndef SHA2_H
#define SHA2_H

#include <cstdint> // Для uint8_t, uint32_t, uint64_t
#include <cstring> // Для memcpy, memset

// Общие определения
#define SHA256_BLOCK_SIZE  64  // 512 бит
#define SHA512_BLOCK_SIZE 128 // 1024 бит

// Размеры дайджестов
#define SHA224_DIGEST_SIZE 28
#define SHA256_DIGEST_SIZE 32
#define SHA384_DIGEST_SIZE 48
#define SHA512_DIGEST_SIZE 64
#define SHA512_224_DIGEST_SIZE 28
#define SHA512_256_DIGEST_SIZE 32

// --- Базовый класс для общей логики SHA-2 ---
class SHA2_Base {
public:
    // Виртуальный деструктор для корректного удаления
    virtual ~SHA2_Base() = default;

    // Инициализация хеш-функции
    void init();

    // Обновление хеша с новыми данными
    void update(const uint8_t* data, size_t length);

    // Завершение хеширования и получение результата
    // size_t digest_size - фактический размер дайджеста для конкретной версии
    void finalize(uint8_t* digest, size_t digest_size);

protected:
    // Конструктор -protected, так как класс базовый
    SHA2_Base(uint8_t block_size_bytes);

    uint8_t m_block_size_bytes; // Размер блока в байтах (64 или 128)
    uint8_t m_buffer[SHA512_BLOCK_SIZE]; // Максимальный буфер для 128 байт
    uint32_t m_buffer_idx;              // Индекс текущей позиции в буфере
    uint64_t m_bit_count;               // Общее количество обработанных бит

    // Чисто виртуальные функции, которые должны быть реализованы в производных классах
    virtual void init_hash_values() = 0; // Инициализация начальных H значений
    virtual void transform() = 0;        // Обработка одного блока
    virtual void get_digest_bytes(uint8_t* digest) = 0; // Копирование H значений в байты

    // Вспомогательная функция для дополнения (padding)
    void pad_message_and_transform();
};

// --- Семейство SHA-256 (32-битные операции) ---
class SHA256_Family : public SHA2_Base {
protected:
    SHA256_Family(); // Конструктор для наследования

    uint32_t m_h[8]; // Промежуточные значения хеша (H0 - H7)

    // Реализация чисто виртуальных функций из SHA2_Base
    void transform() override;
    void get_digest_bytes(uint8_t* digest) override;

    // Вспомогательные функции для битовых операций (32-битные)
    static uint32_t rotr32(uint32_t x, uint32_t n);
    static uint32_t shr32(uint32_t x, uint32_t n);
    static uint32_t ch32(uint32_t x, uint32_t y, uint32_t z);
    static uint32_t maj32(uint32_t x, uint32_t y, uint32_t z);
    static uint32_t sigma0_32(uint32_t x);
    static uint32_t sigma1_32(uint32_t x);
    static uint32_t e_sigma0_32(uint32_t x);
    static uint32_t e_sigma1_32(uint32_t x);
};

// --- Семейство SHA-512 (64-битные операции) ---
class SHA512_Family : public SHA2_Base {
protected:
    SHA512_Family(); // Конструктор для наследования

    uint64_t m_h[8]; // Промежуточные значения хеша (H0 - H7)

    // Реализация чисто виртуальных функций из SHA2_Base
    void transform() override;
    void get_digest_bytes(uint8_t* digest) override;

    // Вспомогательные функции для битовых операций (64-битные)
    static uint64_t rotr64(uint64_t x, uint64_t n);
    static uint64_t shr64(uint64_t x, uint64_t n);
    static uint64_t ch64(uint64_t x, uint64_t y, uint64_t z);
    static uint64_t maj64(uint64_t x, uint64_t y, uint64_t z);
    static uint64_t sigma0_64(uint64_t x);
    static uint64_t sigma1_64(uint64_t x);
    static uint64_t e_sigma0_64(uint64_t x);
    static uint64_t e_sigma1_64(uint64_t x);
};

// --- Конкретные реализации SHA-224, SHA-256 ---
class SHA224 : public SHA256_Family {
public:
    SHA224();
    void finalize(uint8_t digest[SHA224_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

class SHA256 : public SHA256_Family {
public:
    SHA256();
    void finalize(uint8_t digest[SHA256_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

// --- Конкретные реализации SHA-384, SHA-512, SHA-512/224, SHA-512/256 ---
class SHA384 : public SHA512_Family {
public:
    SHA384();
    void finalize(uint8_t digest[SHA384_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

class SHA512 : public SHA512_Family {
public:
    SHA512();
    void finalize(uint8_t digest[SHA512_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

class SHA512_224 : public SHA512_Family {
public:
    SHA512_224();
    void finalize(uint8_t digest[SHA512_224_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

class SHA512_256 : public SHA512_Family {
public:
    SHA512_256();
    void finalize(uint8_t digest[SHA512_256_DIGEST_SIZE]);
protected:
    void init_hash_values() override;
};

// --- Константы SHA-256 ---
static const uint32_t K256[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xe4dbfacc, 0xf00327ed,
    0xf57c0faf, 0x6f07d2dc, 0x720a67ab, 0x81c4c92e, 0x9289297d, 0xa2c8c94e, 0xac42292a, 0xc55c7a1c,
    0xe479b7a1, 0xebf201e1, 0xfa7270f3, 0xfdc488c0, 0x2117559b, 0x33b006a1, 0x4785264b, 0x4cb0a9dc
};

// Начальные значения хеша SHA-256
static const uint32_t H256_INIT[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Начальные значения хеша SHA-224 (первые 8 простых чисел ^ 1/2, усеченные до 224 бит)
static const uint32_t H224_INIT[8] = {
    0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
    0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
};

// --- Константы SHA-512 ---
static const uint64_t K512[80] = {
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f4a337653ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2b6100c7ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bc9566fa1ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xe4dbfacc34ed1a4aULL, 0xf00327edb87dbfceULL,
    0xf57c0fafedbb4f8eULL, 0x6f07d2dc24477610ULL, 0x720a67ab766e257aULL, 0x81c4c92e47edaee6ULL,
    0x9289297d2871fbd4ULL, 0xa2c8c94e47d21384ULL, 0xac42292a434c449cULL, 0xc55c7a1c72a8c8e6ULL,
    0xc67178f2e3725a66ULL, 0xd1b020703f514869ULL, 0xd4d80a13d712e52eULL, 0xdd623f7215163777ULL,
    0xe0033286b245a498ULL, 0xe4b51c19b6ef72e1ULL, 0xeb07d2d3a3754b23ULL, 0xf769ea821cbfe980ULL,
    0xfc6543216893693fULL, 0xfd8655ed59e984f4ULL, 0x01a33a921ed0f4b3ULL, 0x0c681283d6a2f392ULL,
    0x147814a5118525b6ULL, 0x217088f1754f15d0ULL, 0x2748774c47d79b69ULL, 0x2d0c2e9b0b4b2397ULL,
    0x34b0bcb5e1719b36ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
    0x682e6ff3d6b2b8a3ULL, 0x748f82ee5370d919ULL, 0x78a5636f43e5c709ULL, 0x84c87814a1c5d985ULL,
    0x8cc702081a6439ecULL, 0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xa82b40b8a4f9bc08ULL,
    0xbef9a3f7b2c67915ULL, 0xc67178f2e3725a66ULL, 0xcc785bc3e2b7e192ULL, 0xe4dbfacc34ed1a4aULL,
    0xe53028198f2b2176ULL, 0xf769ea821cbfe980ULL, 0xfa7270f3ed02e077ULL, 0xfc6543216893693fULL
};

// Начальные значения хеша SHA-512
static const uint64_t H512_INIT[8] = {
    0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
    0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
};

// Начальные значения хеша SHA-384
static const uint64_t H384_INIT[8] = {
    0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL, 0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
    0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL, 0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL
};

// Начальные значения хеша SHA-512/224
static const uint64_t H512_224_INIT[8] = {
    0x8c3d05260f898c6bULL, 0x741d402b8586cdd2ULL, 0x77037e37ed3c4606ULL, 0xee0a0d2e6097d9d0ULL,
    0x2c64baf86b723703ULL, 0x23ee733792c903a1ULL, 0xd0e01763741a8753ULL, 0x2213264996d51c10ULL
};

// Начальные значения хеша SHA-512/256
static const uint64_t H512_256_INIT[8] = {
    0x22312194fc2bf72cULL, 0x9f555fa3c84c64c2ULL, 0x2393b86b6f53b151ULL, 0x963877195940eabdULL,
    0x96283ee2a88effe3ULL, 0xbe5e1e2553863992ULL, 0x2b0199fc2c658461ULL, 0x0ab63df0a2c5f1cdULL
};

// --- Реализация SHA2_Base ---
SHA2_Base::SHA2_Base(uint8_t block_size_bytes) :
    m_block_size_bytes(block_size_bytes) {
    init();
}

void SHA2_Base::init() {
    init_hash_values(); // Вызывается виртуальная функция для инициализации H
    m_buffer_idx = 0;
    m_bit_count = 0;
}

void SHA2_Base::update(const uint8_t* data, size_t length) {
    m_bit_count += (uint64_t)length * 8; // Обновляем общее количество бит

    size_t data_idx = 0;
    while (length > 0) {
        size_t bytes_to_copy = m_block_size_bytes - m_buffer_idx;
        if (bytes_to_copy > length) {
            bytes_to_copy = length;
        }

        memcpy(m_buffer + m_buffer_idx, data + data_idx, bytes_to_copy);
        m_buffer_idx += bytes_to_copy;
        data_idx += bytes_to_copy;
        length -= bytes_to_copy;

        if (m_buffer_idx == m_block_size_bytes) {
            transform(); // Вызывается виртуальная функция для обработки блока
            m_buffer_idx = 0;
        }
    }
}

void SHA2_Base::finalize(uint8_t* digest, size_t digest_size) {
    pad_message_and_transform(); // Выполняем дополнение и обработку последних блоков
    get_digest_bytes(digest);    // Копируем H значения в байты

    // Обрезаем хеш до нужного размера, если это необходимо
    if (digest_size < SHA512_DIGEST_SIZE && m_block_size_bytes == SHA512_BLOCK_SIZE) {
        // Для SHA-384, SHA-512/224, SHA-512/256
        // digest уже имеет необходимый размер, но мы должны обрезать его
        // (На самом деле, finalize будет принимать digest нужного размера,
        // поэтому копирование только нужного количества байт уже будет достаточно)
    } else if (digest_size < SHA256_DIGEST_SIZE && m_block_size_bytes == SHA256_BLOCK_SIZE) {
        // Для SHA-224
        // Аналогично, digest уже будет нужного размера
    }

    // Сбрасываем состояние для возможности повторного использования
    init();
}

void SHA2_Base::pad_message_and_transform() {
    // 1. Добавляем '1' бит (0x80)
    m_buffer[m_buffer_idx++] = 0x80;

    // 2. Если осталось недостаточно места для длины (8 байт для SHA256-семейства, 16 для SHA512-семейства),
    //    дополняем нулями и обрабатываем блок
    uint8_t length_field_size = (m_block_size_bytes == SHA256_BLOCK_SIZE) ? 8 : 16;
    if (m_buffer_idx > m_block_size_bytes - length_field_size) {
        memset(m_buffer + m_buffer_idx, 0, m_block_size_bytes - m_buffer_idx);
        transform();
        m_buffer_idx = 0;
    }

    // 3. Дополняем нулями до последних 'length_field_size' байтов блока
    memset(m_buffer + m_buffer_idx, 0, m_block_size_bytes - length_field_size - m_buffer_idx);

    // 4. Добавляем длину сообщения в битах (Big-endian)
    if (m_block_size_bytes == SHA256_BLOCK_SIZE) { // Для SHA-256/224 (8 байт длины)
        m_buffer[m_block_size_bytes - 8] = (uint8_t)((m_bit_count >> 56) & 0xFF);
        m_buffer[m_block_size_bytes - 7] = (uint8_t)((m_bit_count >> 48) & 0xFF);
        m_buffer[m_block_size_bytes - 6] = (uint8_t)((m_bit_count >> 40) & 0xFF);
        m_buffer[m_block_size_bytes - 5] = (uint8_t)((m_bit_count >> 32) & 0xFF);
        m_buffer[m_block_size_bytes - 4] = (uint8_t)((m_bit_count >> 24) & 0xFF);
        m_buffer[m_block_size_bytes - 3] = (uint8_t)((m_bit_count >> 16) & 0xFF);
        m_buffer[m_block_size_bytes - 2] = (uint8_t)((m_bit_count >> 8) & 0xFF);
        m_buffer[m_block_size_bytes - 1] = (uint8_t)(m_bit_count & 0xFF);
    } else { // Для SHA-512/384/512/224/512/256 (16 байт длины)
        // Общая длина сообщения в битах - это m_bit_count (uint64_t).
        // SHA-512 использует 128-битное представление длины, но с учетом того,
        // что m_bit_count - это uint64_t, старшие 64 бита (которые должны быть нулями) не используются.
        // Это обычно не проблема, так как длина сообщения редко превышает 2^64 бита.
        memset(m_buffer + m_block_size_bytes - 16, 0, 8); // Старшие 8 байт для длины (обычно 0)
        m_buffer[m_block_size_bytes - 8]  = (uint8_t)((m_bit_count >> 56) & 0xFF);
        m_buffer[m_block_size_bytes - 7]  = (uint8_t)((m_bit_count >> 48) & 0xFF);
        m_buffer[m_block_size_bytes - 6]  = (uint8_t)((m_bit_count >> 40) & 0xFF);
        m_buffer[m_block_size_bytes - 5]  = (uint8_t)((m_bit_count >> 32) & 0xFF);
        m_buffer[m_block_size_bytes - 4]  = (uint8_t)((m_bit_count >> 24) & 0xFF);
        m_buffer[m_block_size_bytes - 3]  = (uint8_t)((m_bit_count >> 16) & 0xFF);
        m_buffer[m_block_size_bytes - 2]  = (uint8_t)((m_bit_count >> 8) & 0xFF);
        m_buffer[m_block_size_bytes - 1]  = (uint8_t)(m_bit_count & 0xFF);
    }

    // 5. Обрабатываем последний блок
    transform();
}

// --- Реализация SHA256_Family (32-битные операции) ---
SHA256_Family::SHA256_Family() : SHA2_Base(SHA256_BLOCK_SIZE) {}

// Вспомогательные функции (32-битные)
uint32_t SHA256_Family::rotr32(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}
uint32_t SHA256_Family::shr32(uint32_t x, uint32_t n) {
    return x >> n;
}
uint32_t SHA256_Family::ch32(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}
uint32_t SHA256_Family::maj32(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}
uint32_t SHA256_Family::sigma0_32(uint32_t x) {
    return rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22);
}
uint32_t SHA256_Family::sigma1_32(uint32_t x) {
    return rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25);
}
uint32_t SHA256_Family::e_sigma0_32(uint32_t x) {
    return rotr32(x, 7) ^ rotr32(x, 18) ^ shr32(x, 3);
}
uint32_t SHA256_Family::e_sigma1_32(uint32_t x) {
    return rotr32(x, 17) ^ rotr32(x, 19) ^ shr32(x, 10);
}

void SHA256_Family::transform() {
    uint32_t W[64];

    for (int i = 0; i < 16; ++i) {
        W[i] = (uint32_t)m_buffer[i * 4] << 24 |
               (uint32_t)m_buffer[i * 4 + 1] << 16 |
               (uint32_t)m_buffer[i * 4 + 2] << 8 |
               (uint32_t)m_buffer[i * 4 + 3];
    }

    for (int i = 16; i < 64; ++i) {
        W[i] = e_sigma1_32(W[i - 2]) + W[i - 7] + e_sigma0_32(W[i - 15]) + W[i - 16];
    }

    uint32_t a = m_h[0];
    uint32_t b = m_h[1];
    uint32_t c = m_h[2];
    uint32_t d = m_h[3];
    uint32_t e = m_h[4];
    uint32_t f = m_h[5];
    uint32_t g = m_h[6];
    uint32_t h = m_h[7];

    uint32_t T1, T2;

    for (int i = 0; i < 64; ++i) {
        T1 = h + sigma1_32(e) + ch32(e, f, g) + K256[i] + W[i];
        T2 = sigma0_32(a) + maj32(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    m_h[0] += a;
    m_h[1] += b;
    m_h[2] += c;
    m_h[3] += d;
    m_h[4] += e;
    m_h[5] += f;
    m_h[6] += g;
    m_h[7] += h;
}

void SHA256_Family::get_digest_bytes(uint8_t* digest) {
    for (int i = 0; i < 8; ++i) {
        digest[i * 4]     = (uint8_t)((m_h[i] >> 24) & 0xFF);
        digest[i * 4 + 1] = (uint8_t)((m_h[i] >> 16) & 0xFF);
        digest[i * 4 + 2] = (uint8_t)((m_h[i] >> 8) & 0xFF);
        digest[i * 4 + 3] = (uint8_t)(m_h[i] & 0xFF);
    }
}

// --- Реализация SHA512_Family (64-битные операции) ---
SHA512_Family::SHA512_Family() : SHA2_Base(SHA512_BLOCK_SIZE) {}

// Вспомогательные функции (64-битные)
uint64_t SHA512_Family::rotr64(uint64_t x, uint64_t n) {
    return (x >> n) | (x << (64 - n));
}
uint64_t SHA512_Family::shr64(uint64_t x, uint64_t n) {
    return x >> n;
}
uint64_t SHA512_Family::ch64(uint64_t x, uint64_t y, uint64_t z) {
    return (x & y) ^ (~x & z);
}
uint64_t SHA512_Family::maj64(uint64_t x, uint64_t y, uint64_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}
uint64_t SHA512_Family::sigma0_64(uint64_t x) {
    return rotr64(x, 28) ^ rotr64(x, 34) ^ rotr64(x, 39);
}
uint64_t SHA512_Family::sigma1_64(uint64_t x) {
    return rotr64(x, 14) ^ rotr64(x, 18) ^ rotr64(x, 41);
}
uint64_t SHA512_Family::e_sigma0_64(uint64_t x) {
    return rotr64(x, 1) ^ rotr64(x, 8) ^ shr64(x, 7);
}
uint64_t SHA512_Family::e_sigma1_64(uint64_t x) {
    return rotr64(x, 19) ^ rotr64(x, 61) ^ shr64(x, 6);
}

void SHA512_Family::transform() {
    uint64_t W[80];

    // Копируем 16 слов (1024 бит) из буфера в W[0...15]
    for (int i = 0; i < 16; ++i) {
        W[i] = (uint64_t)m_buffer[i * 8] << 56 |
               (uint64_t)m_buffer[i * 8 + 1] << 48 |
               (uint64_t)m_buffer[i * 8 + 2] << 40 |
               (uint64_t)m_buffer[i * 8 + 3] << 32 |
               (uint64_t)m_buffer[i * 8 + 4] << 24 |
               (uint64_t)m_buffer[i * 8 + 5] << 16 |
               (uint64_t)m_buffer[i * 8 + 6] << 8 |
               (uint64_t)m_buffer[i * 8 + 7];
    }

    // Расширяем W[16...79]
    for (int i = 16; i < 80; ++i) {
        W[i] = e_sigma1_64(W[i - 2]) + W[i - 7] + e_sigma0_64(W[i - 15]) + W[i - 16];
    }

    uint64_t a = m_h[0];
    uint64_t b = m_h[1];
    uint64_t c = m_h[2];
    uint64_t d = m_h[3];
    uint64_t e = m_h[4];
    uint64_t f = m_h[5];
    uint64_t g = m_h[6];
    uint64_t h = m_h[7];

    uint64_t T1, T2;

    // Основной цикл сжатия (80 раундов)
    for (int i = 0; i < 80; ++i) {
        T1 = h + sigma1_64(e) + ch64(e, f, g) + K512[i] + W[i];
        T2 = sigma0_64(a) + maj64(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Обновление промежуточных хеш-значений
    m_h[0] += a;
    m_h[1] += b;
    m_h[2] += c;
    m_h[3] += d;
    m_h[4] += e;
    m_h[5] += f;
    m_h[6] += g;
    m_h[7] += h;
}

void SHA512_Family::get_digest_bytes(uint8_t* digest) {
    for (int i = 0; i < 8; ++i) {
        digest[i * 8]     = (uint8_t)((m_h[i] >> 56) & 0xFF);
        digest[i * 8 + 1] = (uint8_t)((m_h[i] >> 48) & 0xFF);
        digest[i * 8 + 2] = (uint8_t)((m_h[i] >> 40) & 0xFF);
        digest[i * 8 + 3] = (uint8_t)((m_h[i] >> 32) & 0xFF);
        digest[i * 8 + 4] = (uint8_t)((m_h[i] >> 24) & 0xFF);
        digest[i * 8 + 5] = (uint8_t)((m_h[i] >> 16) & 0xFF);
        digest[i * 8 + 6] = (uint8_t)((m_h[i] >> 8) & 0xFF);
        digest[i * 8 + 7] = (uint8_t)(m_h[i] & 0xFF);
    }
}

// --- Реализация конкретных классов SHA256_Family ---
SHA224::SHA224() {} // Конструктор базового класса уже вызван
void SHA224::init_hash_values() { memcpy(m_h, H224_INIT, sizeof(m_h)); }
void SHA224::finalize(uint8_t digest[SHA224_DIGEST_SIZE]) {
    SHA2_Base::finalize(digest, SHA224_DIGEST_SIZE);
}

SHA256::SHA256() {}
void SHA256::init_hash_values() { memcpy(m_h, H256_INIT, sizeof(m_h)); }
void SHA256::finalize(uint8_t digest[SHA256_DIGEST_SIZE]) {
    SHA2_Base::finalize(digest, SHA256_DIGEST_SIZE);
}

// --- Реализация конкретных классов SHA512_Family ---
SHA384::SHA384() {}
void SHA384::init_hash_values() { memcpy(m_h, H384_INIT, sizeof(m_h)); }
void SHA384::finalize(uint8_t digest[SHA384_DIGEST_SIZE]) {
    // SHA-384 использует начальные H-значения от SHA-512, но усекает вывод
    SHA2_Base::finalize(digest, SHA384_DIGEST_SIZE);
}

SHA512::SHA512() {}
void SHA512::init_hash_values() { memcpy(m_h, H512_INIT, sizeof(m_h)); }
void SHA512::finalize(uint8_t digest[SHA512_DIGEST_SIZE]) {
    SHA2_Base::finalize(digest, SHA512_DIGEST_SIZE);
}

SHA512_224::SHA512_224() {}
void SHA512_224::init_hash_values() { memcpy(m_h, H512_224_INIT, sizeof(m_h)); }
void SHA512_224::finalize(uint8_t digest[SHA512_224_DIGEST_SIZE]) {
    SHA2_Base::finalize(digest, SHA512_224_DIGEST_SIZE);
}

SHA512_256::SHA512_256() {}
void SHA512_256::init_hash_values() { memcpy(m_h, H512_256_INIT, sizeof(m_h)); }
void SHA512_256::finalize(uint8_t digest[SHA512_256_DIGEST_SIZE]) {
    SHA2_Base::finalize(digest, SHA512_256_DIGEST_SIZE);
}

#endif // __SHA2__

#ifndef __SHA3__
#define __SHA3__

// Define macros for bitwise rotations, optimized for fixed-width types
#define ROTL64(x, n) (((x) << (n)) | ((x) >> (64 - (n))))

// --- SHA3 Class Definition ---
class SHA3 {
public:
    // Constructor (optional, can be empty as state is initialized in init())
    SHA3();

    // Initialize the hash function for a specific output size
    // For SHA3-224, 256, 384, 512. For SHAKE, use the SHAKE functions directly.
    void init(unsigned int outputBits);

    // Update the hash with input data
    void update(const uint8_t* data, size_t len);

    // Finalize the hash computation and get the digest
    void final(uint8_t* digest);

    // Specific SHA3-fixed output functions
    void sha3_224(const uint8_t* data, size_t len, uint8_t* digest);
    void sha3_256(const uint8_t* data, size_t len, uint8_t* digest);
    void sha3_384(const uint8_t* data, size_t len, uint8_t* digest);
    void sha3_512(const uint8_t* data, size_t len, uint8_t* digest);

    // SHAKE functions (XOF - eXtendable Output Function)
    void shake128_init();
    void shake256_init();
    void shake_update(const uint8_t* data, size_t len);
    void shake_squeeze(uint8_t* output, size_t len);

private:
    // Keccak state: 5x5 array of 64-bit lanes (1600 bits total)
    uint64_t state[5][5];

    // Current block buffer
    uint8_t block[200]; // Max block size for Keccak-f[1600] is 200 bytes (1600 bits)

    size_t blockLen;       // Current bytes in block
    unsigned int rate;     // Rate in bits (R)
    unsigned int capacity; // Capacity in bits (C)
    unsigned int outputLen; // Output length in bits (for fixed SHA3 functions)
    uint8_t d;             // Padding byte for SHA-3 (0x06) or SHAKE (0x1F)

    // Private helper functions
    void keccak_absorb(const uint8_t* data, size_t len);
    void keccak_squeeze(uint8_t* output, size_t len);
    void keccak_permutation();
    void keccak_set_parameters(unsigned int outputBits, bool isSHAKE);
    void pad_and_absorb_last_block();
    void clear_state();
};

// --- SHA3 Class Implementation ---

SHA3::SHA3() {
    clear_state();
    blockLen = 0;
    rate = 0;
    capacity = 0;
    outputLen = 0;
    d = 0;
}

void SHA3::clear_state() {
    memset(state, 0, sizeof(state));
    memset(block, 0, sizeof(block));
}

// Keccak-f[1600] permutation round constants
static const uint64_t KeccakP1600RoundConstants[24] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL,
    0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
    0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL,
    0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
    0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL,
    0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
    0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL,
    0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

// Keccak-f[1600] permutation
void SHA3::keccak_permutation() {
    uint64_t A[5][5];
    uint64_t C[5], D[5];
    uint64_t B[5][5];

    // Copy current state to working A
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            A[x][y] = state[x][y];
        }
    }

    for (int round = 0; round < 24; ++round) {
        // Theta step
        for (int x = 0; x < 5; ++x) {
            C[x] = A[x][0] ^ A[x][1] ^ A[x][2] ^ A[x][3] ^ A[x][4];
        }
        for (int x = 0; x < 5; ++x) {
            D[x] = C[(x + 4) % 5] ^ ROTL64(C[(x + 1) % 5], 1);
            for (int y = 0; y < 5; ++y) {
                A[x][y] ^= D[x];
            }
        }

        // Rho and Pi steps
        int x = 1, y = 0;
        uint64_t current = A[x][y];
        for (int t = 0; t < 24; ++t) {
            int newX = y;
            int newY = (2 * x + 3 * y) % 5;
            int rotVal = (t + 1) * (t + 2) / 2 % 64; // Rotation offset for Pi step
            B[newX][newY] = ROTL64(current, rotVal);
            current = A[newX][newY];
            x = newX;
            y = newY;
        }

        // Chi step
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y < 5; ++y) {
                A[x][y] = B[x][y] ^ ((~B[(x + 1) % 5][y]) & B[(x + 2) % 5][y]);
            }
        }

        // Iota step
        A[0][0] ^= KeccakP1600RoundConstants[round];
    }

    // Copy back to actual state
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 5; ++y) {
            state[x][y] = A[x][y];
        }
    }
}

// Converts bytes to 64-bit lanes (little-endian)
static uint64_t bytes_to_u64(const uint8_t* bytes) {
    uint64_t val = 0;
    for (int i = 0; i < 8; ++i) {
        val |= (uint64_t)bytes[i] << (i * 8);
    }
    return val;
}

// Converts 64-bit lanes to bytes (little-endian)
static void u64_to_bytes(uint664_t val, uint8_t* bytes) {
    for (int i = 0; i < 8; ++i) {
        bytes[i] = (uint8_t)(val >> (i * 8));
    }
}

void SHA3::keccak_set_parameters(unsigned int outputBits, bool isSHAKE) {
    clear_state();
    outputLen = outputBits;

    if (isSHAKE) {
        // SHAKE functions
        if (outputBits == 128) {
            rate = 1344; // 168 bytes
            capacity = 256;
            d = 0x1F; // SHAKE padding suffix
        } else if (outputBits == 256) {
            rate = 1088; // 136 bytes
            capacity = 512;
            d = 0x1F; // SHAKE padding suffix
        } else {
            // Should not happen if called correctly for SHAKE128/256
        }
    } else {
        // SHA3 fixed-output functions
        switch (outputBits) {
            case 224:
                rate = 1152; // 144 bytes
                capacity = 448;
                break;
            case 256:
                rate = 1088; // 136 bytes
                capacity = 512;
                break;
            case 384:
                rate = 832; // 104 bytes
                capacity = 768;
                break;
            case 512:
                rate = 576; // 72 bytes
                capacity = 1024;
                break;
            default:
                // Error handling or throw exception if desired
                return;
        }
        d = 0x06; // SHA-3 padding suffix
    }
    blockLen = 0; // Reset block buffer
}

// Absorb phase for Keccak
void SHA3::keccak_absorb(const uint8_t* data, size_t len) {
    size_t rate_bytes = rate / 8; // Rate in bytes

    while (len > 0) {
        size_t copy_len = rate_bytes - blockLen;
        if (copy_len > len) {
            copy_len = len;
        }

        memcpy(&block[blockLen], data, copy_len);
        blockLen += copy_len;
        data += copy_len;
        len -= copy_len;

        if (blockLen == rate_bytes) {
            // Absorb the block into the state
            for (size_t i = 0; i < rate_bytes / 8; ++i) {
                state[i % 5][i / 5] ^= bytes_to_u64(&block[i * 8]);
            }
            keccak_permutation();
            blockLen = 0;
        }
    }
}

// Padding and absorb the last block (SHA3 specific: 0x06, SHAKE specific: 0x1F)
void SHA3::pad_and_absorb_last_block() {
    size_t rate_bytes = rate / 8;

    // Append 0x01 (or 0x1F for SHAKE)
    block[blockLen++] = d;

    // Pad with zeros
    while (blockLen < rate_bytes) {
        block[blockLen++] = 0x00;
    }

    // Append 0x80
    block[rate_bytes - 1] |= 0x80;

    // Absorb the last block
    for (size_t i = 0; i < rate_bytes / 8; ++i) {
        state[i % 5][i / 5] ^= bytes_to_u64(&block[i * 8]);
    }
    keccak_permutation();
}

// Squeeze phase for Keccak
void SHA3::keccak_squeeze(uint8_t* output, size_t len) {
    size_t rate_bytes = rate / 8;

    size_t output_bytes_count = 0;
    while (output_bytes_count < len) {
        size_t copy_len = len - output_bytes_count;
        if (copy_len > rate_bytes) {
            copy_len = rate_bytes;
        }

        for (size_t i = 0; i < copy_len / 8; ++i) {
            u64_to_bytes(state[i % 5][i / 5], &output[output_bytes_count + i * 8]);
        }
        
        // Handle remaining bytes if copy_len is not a multiple of 8
        if (copy_len % 8 != 0) {
             uint8_t temp_lane_bytes[8];
             u64_to_bytes(state[(copy_len / 8) % 5][(copy_len / 8) / 5], temp_lane_bytes);
             memcpy(&output[output_bytes_count + (copy_len / 8) * 8], temp_lane_bytes, copy_len % 8);
        }

        output_bytes_count += copy_len;
        
        if (output_bytes_count < len) {
            keccak_permutation(); // Permute if more output is needed
        }
    }
}

// --- Public API for SHA3 fixed output ---

void SHA3::init(unsigned int outputBits) {
    keccak_set_parameters(outputBits, false);
}

void SHA3::update(const uint8_t* data, size_t len) {
    keccak_absorb(data, len);
}

void SHA3::final(uint8_t* digest) {
    pad_and_absorb_last_block();
    keccak_squeeze(digest, outputLen / 8);
    clear_state(); // Clear state after finalization
}

void SHA3::sha3_224(const uint8_t* data, size_t len, uint8_t* digest) {
    init(224);
    update(data, len);
    final(digest);
}

void SHA3::sha3_256(const uint8_t* data, size_t len, uint8_t* digest) {
    init(256);
    update(data, len);
    final(digest);
}

void SHA3::sha3_384(const uint8_t* data, size_t len, uint8_t* digest) {
    init(384);
    update(data, len);
    final(digest);
}

void SHA3::sha3_512(const uint8_t* data, size_t len, uint8_t* digest) {
    init(512);
    update(data, len);
    final(digest);
}

// --- Public API for SHAKE (XOF) ---

void SHA3::shake128_init() {
    keccak_set_parameters(128, true);
}

void SHA3::shake256_init() {
    keccak_set_parameters(256, true);
}

void SHA3::shake_update(const uint8_t* data, size_t len) {
    keccak_absorb(data, len);
}

void SHA3::shake_squeeze(uint8_t* output, size_t len) {
    // This is called AFTER all input has been absorbed.
    // The padding needs to be applied only once before the first squeeze call.
    // To handle multiple squeeze calls, we need a flag.
    // For simplicity here, assume squeeze is called after all updates and before further updates.
    // A more robust XOF would manage an 'absorbing' vs 'squeezing' state.

    // A simple approach for this context: if blockLen > 0, it means we are still in absorbing state.
    // Pad and permute only if we haven't entered the squeezing phase yet for this context.
    if (blockLen > 0 || state[0][0] == 0) { // Check if padding is needed (simple check if state is initial or not fully absorbed)
        pad_and_absorb_last_block();
    }
    keccak_squeeze(output, len);
}

#endif /* __SHA3__ */

#ifndef __CRC__
#define __CRC__
e_event__e crc32(u32* result, u32 len, const void *data, u32 polynom) {
    // Стандартный полином для STM32 0x04C11DB7
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
    const unsigned char *buffer = dynamic_cast<const unsigned char*>(data);
    u32 crc = -1;
    while(len--) {
        crc = pow(crc, static_cast<u32>((*buffer++) << 24));
        for( int bit = 0; bit < 8; bit++ )
            crc = crc & (1L << 31) ? pow((crc << 1), polynom) : (crc << 1);
    }
    u32 res {reflect32(~crc)};
    result = &res;
    return E_EVENT_OK;
}
#endif /* __CRC_PROGRAMABLE__ */

#endif /* __CRYPTO__ */