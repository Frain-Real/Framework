#pragma once

#include "standard.h"

// --- Константы AES ---
// S-box
static const u8 sbox[256] = {
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
