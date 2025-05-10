// Математические функции эмуляции фильтров, мат. расчётов и другого
#include "standard.h"
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
u32 random() {
  static u32 seed = 5; // зерно не должно быть 0
  seed = (seed * 73129 + 95121) % 100000;
  return seed;
}
#endif /* __RND_PROGRAMABLE__ */

/********          AES             *******/
#ifdef __AES_PROGRAMABLE__
// --- Константы AES ---
// Количество колонок в состоянии (128 бит / 32 бита на слово = 4)
#define NB 4 
// Длина ключа в словах (128 бит / 32 бита на слово = 4)
#define NK 4 
// Количество раундов для 128-битного ключа
#define NR 10 

class AESCipher {
public:
    // Конструктор: инициализирует объект класса.
    // Важно: ключ должен быть 16-байтным.
    AESCipher(const uint8_t* key) {
        // Копируем предоставленный ключ
        memcpy(roundKeys[0], key, 16); 
        // Выполняем расширение ключа
        KeyExpansion(); 
    }

    // Метод для шифрования одного блока данных (16 байт).
    // inputBlock: указатель на 16-байтный блок данных для шифрования.
    // outputBlock: указатель на буфер, куда будет записан зашифрованный 16-байтный блок.
    void EncryptBlock(const uint8_t* inputBlock, uint8_t* outputBlock) const {
        // Копируем входной блок в буфер состояния
        uint8_t state[4][4]; // Представляем блок как матрицу 4x4
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                state[j][i] = inputBlock[i * 4 + j];
            }
        }

        // Первый раунд: только AddRoundKey
        AddRoundKey(state, 0); 

        // 9 раундов шифрования (для 128-битного ключа NR-1)
        for (int round = 1; round < NR; ++round) {
            SubBytes(state);
            ShiftRows(state);
            MixColumns(state);
            AddRoundKey(state, round);
        }

        // Последний раунд: без MixColumns
        SubBytes(state);
        ShiftRows(state);
        AddRoundKey(state, NR);

        // Копируем зашифрованный блок из состояния в выходной буфер
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                outputBlock[i * 4 + j] = state[j][i];
            }
        }
    }

    // Метод для расшифрования одного блока данных (16 байт).
    // inputBlock: указатель на 16-байтный зашифрованный блок.
    // outputBlock: указатель на буфер, куда будет записан расшифрованный 16-байтный блок.
    void DecryptBlock(const uint8_t* inputBlock, uint8_t* outputBlock) const {
        // Копируем входной блок в буфер состояния
        uint8_t state[4][4];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                state[j][i] = inputBlock[i * 4 + j];
            }
        }

        // Первый раунд расшифрования: AddRoundKey (последний раунд шифрования)
        AddRoundKey(state, NR);

        // 9 раундов расшифрования (для 128-битного ключа NR-1)
        for (int round = NR - 1; round > 0; --round) {
            InvShiftRows(state);
            InvSubBytes(state);
            AddRoundKey(state, round);
            InvMixColumns(state);
        }

        // Последний раунд расшифрования: без InvMixColumns
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, 0); // Первый раунд шифрования

        // Копируем расшифрованный блок из состояния в выходной буфер
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                outputBlock[i * 4 + j] = state[j][i];
            }
        }
    }

private:
    // Массив для хранения раундовых ключей.
    // NR + 1 раундов, каждый раундовый ключ - это 16 байт (4 слова по 4 байта).
    uint8_t roundKeys[NR + 1][NB * 4]; 

    // --- Таблицы преобразований AES (S-Box, InvS-Box, Rcon) ---
    // S-Box для преобразования SubBytes
    static const uint8_t sBox[256];
    // InvS-Box для преобразования InvSubBytes
    static const uint8_t invSBox[256];
    // Rcon для расширения ключа
    static const uint8_t rcon[11];

    // --- Вспомогательные функции ---

    // Функции умножения в поле GF(2^8)
    static uint8_t GFMul(uint8_t a, uint8_t b) {
        uint8_t p = 0;
        uint8_t hiBitSet;
        for (int counter = 0; counter < 8; counter++) {
            if ((b & 1) != 0) {
                p ^= a;
            }
            hiBitSet = (a & 0x80);
            a <<= 1;
            if (hiBitSet != 0) {
                a ^= 0x1B; // 0x1B - это {00011011}
            }
            b >>= 1;
        }
        return p;
    }

    // Применяет S-Box к каждому байту в состоянии.
    void SubBytes(uint8_t state[4][4]) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                state[i][j] = sBox[state[i][j]];
            }
        }
    }

    // Применяет InvS-Box к каждому байту в состоянии.
    void InvSubBytes(uint8_t state[4][4]) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                state[i][j] = invSBox[state[i][j]];
            }
        }
    }

    // Сдвигает строки состояния.
    void ShiftRows(uint8_t state[4][4]) const {
        uint8_t temp;
        // Строка 1: сдвиг на 1
        temp = state[1][0];
        state[1][0] = state[1][1];
        state[1][1] = state[1][2];
        state[1][2] = state[1][3];
        state[1][3] = temp;

        // Строка 2: сдвиг на 2
        temp = state[2][0];
        state[2][0] = state[2][2];
        state[2][2] = temp;
        temp = state[2][1];
        state[2][1] = state[2][3];
        state[2][3] = temp;

        // Строка 3: сдвиг на 3
        temp = state[3][0];
        state[3][0] = state[3][3];
        state[3][3] = state[3][2];
        state[3][2] = state[3][1];
        state[3][1] = temp;
    }

    // Обратный сдвиг строк состояния.
    void InvShiftRows(uint8_t state[4][4]) const {
        uint8_t temp;
        // Строка 1: сдвиг на 1 вправо
        temp = state[1][3];
        state[1][3] = state[1][2];
        state[1][2] = state[1][1];
        state[1][1] = state[1][0];
        state[1][0] = temp;

        // Строка 2: сдвиг на 2 вправо
        temp = state[2][0];
        state[2][0] = state[2][2];
        state[2][2] = temp;
        temp = state[2][1];
        state[2][1] = state[2][3];
        state[2][3] = temp;

        // Строка 3: сдвиг на 3 вправо
        temp = state[3][0];
        state[3][0] = state[3][1];
        state[3][1] = state[3][2];
        state[3][2] = state[3][3];
        state[3][3] = temp;
    }

    // Перемешивает столбцы состояния.
    void MixColumns(uint8_t state[4][4]) const {
        for (int i = 0; i < 4; ++i) {
            uint8_t s0 = state[0][i], s1 = state[1][i], s2 = state[2][i], s3 = state[3][i];
            state[0][i] = GFMul(0x02, s0) ^ GFMul(0x03, s1) ^ s2 ^ s3;
            state[1][i] = s0 ^ GFMul(0x02, s1) ^ GFMul(0x03, s2) ^ s3;
            state[2][i] = s0 ^ s1 ^ GFMul(0x02, s2) ^ GFMul(0x03, s3);
            state[3][i] = GFMul(0x03, s0) ^ s1 ^ s2 ^ GFMul(0x02, s3);
        }
    }

    // Обратное перемешивание столбцов состояния.
    void InvMixColumns(uint8_t state[4][4]) const {
        for (int i = 0; i < 4; ++i) {
            uint8_t s0 = state[0][i], s1 = state[1][i], s2 = state[2][i], s3 = state[3][i];
            state[0][i] = GFMul(0x0E, s0) ^ GFMul(0x0B, s1) ^ GFMul(0x0D, s2) ^ GFMul(0x09, s3);
            state[1][i] = GFMul(0x09, s0) ^ GFMul(0x0E, s1) ^ GFMul(0x0B, s2) ^ GFMul(0x0D, s3);
            state[2][i] = GFMul(0x0D, s0) ^ GFMul(0x09, s1) ^ GFMul(0x0E, s2) ^ GFMul(0x0B, s3);
            state[3][i] = GFMul(0x0B, s0) ^ GFMul(0x0D, s1) ^ GFMul(0x09, s2) ^ GFMul(0x0E, s3);
        }
    }

    // Добавляет раундовый ключ к состоянию.
    void AddRoundKey(uint8_t state[4][4], int round) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                state[j][i] ^= roundKeys[round][i * 4 + j];
            }
        }
    }

    // RotWord - цикличный сдвиг слова на один байт влево.
    uint32_t RotWord(uint32_t word) const {
        return (word << 8) | (word >> 24);
    }

    // SubWord - применяет S-Box к каждому байту слова.
    uint32_t SubWord(uint32_t word) const {
        uint8_t b0 = sBox[(word >> 24) & 0xFF];
        uint8_t b1 = sBox[(word >> 16) & 0xFF];
        uint8_t b2 = sBox[(word >> 8) & 0xFF];
        uint8_t b3 = sBox[word & 0xFF];
        return ((uint32_t)b0 << 24) | ((uint32_t)b1 << 16) | ((uint32_t)b2 << 8) | b3;
    }

    // Расширение ключа: генерирует все раундовые ключи.
    void KeyExpansion() {
        uint32_t temp; // Временная переменная для слова
        int i = NK;    // Индекс текущего слова ключа

        // Копируем исходный ключ в первые NK слов
        // (NK * 4 байт = 16 байт)
        for (int j = 0; j < NK; ++j) {
            roundKeys[0][j * 4 + 0] = roundKeys[0][j * 4 + 0]; // Уже скопировано конструктором
            roundKeys[0][j * 4 + 1] = roundKeys[0][j * 4 + 1];
            roundKeys[0][j * 4 + 2] = roundKeys[0][j * 4 + 2];
            roundKeys[0][j * 4 + 3] = roundKeys[0][j * 4 + 3];
        }

        while (i < NB * (NR + 1)) {
            // Читаем предыдущее слово
            temp = ((uint32_t)roundKeys[0][(i - 1) * 4 + 0] << 24) |
                   ((uint32_t)roundKeys[0][(i - 1) * 4 + 1] << 16) |
                   ((uint32_t)roundKeys[0][(i - 1) * 4 + 2] << 8) |
                   ((uint32_t)roundKeys[0][(i - 1) * 4 + 3]);

            if (i % NK == 0) {
                // RotWord и SubWord применяются только к первому слову каждого NK-го блока
                temp = SubWord(RotWord(temp)) ^ rcon[i / NK];
            } else if (NK > 6 && i % NK == 4) {
                // Для 256-битных ключей
                temp = SubWord(temp);
            }
            
            // XOR с NK-м словом назад
            uint32_t prevWord = ((uint32_t)roundKeys[0][(i - NK) * 4 + 0] << 24) |
                                ((uint32_t)roundKeys[0][(i - NK) * 4 + 1] << 16) |
                                ((uint32_t)roundKeys[0][(i - NK) * 4 + 2] << 8) |
                                ((uint32_t)roundKeys[0][(i - NK) * 4 + 3]);
            temp ^= prevWord;

            // Записываем полученное слово в раундовые ключи
            roundKeys[0][i * 4 + 0] = (uint8_t)(temp >> 24);
            roundKeys[0][i * 4 + 1] = (uint8_t)(temp >> 16);
            roundKeys[0][i * 4 + 2] = (uint8_t)(temp >> 8);
            roundKeys[0][i * 4 + 3] = (uint8_t)temp;

            // Теперь переносим расширенный ключ в `roundKeys` массив
            // Он уже расширяется линейно, но мы используем roundKeys[0] как рабочий буфер.
            // Переносим в соответствующие раунды.
            // i / NB - это номер раунда
            // (i % NB) * 4 - это смещение внутри раунда
            for (int k = 0; k < 4; ++k) {
                 roundKeys[i / NB][(i % NB) * 4 + k] = roundKeys[0][i * 4 + k];
            }

            i++;
        }
    }
};
#undef NB
#undef NK
#undef NR
// --- Инициализация статических членов класса (таблиц) ---
// Эти таблицы должны быть определены вне класса.
const uint8_t AESCipher::sBox[256] = {
    // Таблица S-Box, как в спецификации AES
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5e, 0x73, 0x22,
    0x8b, 0x49, 0x54, 0x16, 0xef, 0x86, 0x42, 0x68, 0x14, 0x74, 0x9b, 0x98, 0x0f, 0x06, 0x5e, 0x61,
    0x4d, 0x19, 0x35, 0x56, 0x2c, 0xbe, 0x20, 0x63, 0x9e, 0xc6, 0x3d, 0xda, 0x5a, 0x41, 0x77, 0xcc,
    0xb0, 0xbd, 0x70, 0x2d, 0x2e, 0x7d, 0x48, 0x2a, 0x8d, 0x90, 0xd9, 0x3a, 0x6f, 0xee, 0x1d, 0x5b,
    0xa1, 0xf4, 0x1e, 0x87, 0x89, 0x0a, 0xbf, 0xb6, 0xc1, 0x02, 0x95, 0x4b, 0xe4, 0x1f, 0xd9, 0xeb,
    0x08, 0x6a, 0x13, 0x78, 0x01, 0xf3, 0x5d, 0x66, 0xfe, 0x83, 0x9a, 0x44, 0x43, 0xda, 0xa8, 0xbe,
    0x4b, 0x0d, 0x2a, 0x2f, 0x81, 0xc6, 0xcd, 0x26, 0x87, 0x6e, 0x49, 0x0b, 0x9e, 0x6b, 0x17, 0x89,
    0x6e, 0x7b, 0x37, 0x29, 0x05, 0x97, 0x4a, 0x9c, 0x86, 0x6f, 0x7c, 0x93, 0x71, 0xcc, 0xd4, 0x61
};

const uint8_t AESCipher::invSBox[256] = {
    // Таблица InvS-Box, как в спецификации AES
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x7a, 0x9f, 0x0e, 0xeb, 0xb0, 0x2b,
    0x2a, 0xf1, 0xd1, 0x7e, 0xdd, 0x47, 0x53, 0x53, 0x19, 0x4a, 0x4b, 0xdb, 0x1a, 0xe1, 0x1c, 0xa9,
    0x0d, 0x0c, 0x86, 0x5b, 0x2a, 0x8d, 0x90, 0x1d, 0xd9, 0x3a, 0x6f, 0xee, 0x1d, 0x5b, 0xa1, 0xf4,
    0x1e, 0x87, 0x89, 0x0a, 0xbf, 0xb6, 0xc1, 0x02, 0x95, 0x4b, 0xe4, 0x1f, 0xd9, 0xeb, 0x08, 0x6a,
    0x13, 0x78, 0x01, 0xf3, 0x5d, 0x66, 0xfe, 0x83, 0x9a, 0x44, 0x43, 0xda, 0xa8, 0xbe, 0x4b, 0x0d,
    0x2a, 0x2f, 0x81, 0xc6, 0xcd, 0x26, 0x87, 0x6e, 0x49, 0x0b, 0x9e, 0x6b, 0x17, 0x89, 0x6e, 0x7b,
    0x37, 0x29, 0x05, 0x97, 0x4a, 0x9c, 0x86, 0x6f, 0x7c, 0x93, 0x71, 0xcc, 0xd4, 0x61, 0xfe, 0xd7
};

const uint8_t AESCipher::rcon[11] = {
    // Rcon значения для расширения ключа
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};
#endif /* __AES_PROGRAMABLE__ */

/********          RSA             *******/
#ifdef __RSA_PROGRAMABLE__
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
#endif /* __RSA_PROGRAMABLE__ */

/********          SHA             *******/
#ifdef __SHA_PROGRAMABLE__
class SHA256 {
public:
    // Публичный метод для вычисления SHA-256 хеша
    void hash(const std::string& message) {
        // Длина исходного сообщения в байтах
        unsigned long long message_len_bytes = message.length();
        // Длина исходного сообщения в битах
        unsigned long long original_bit_len = message_len_bytes * 8;

        // Вычисляем длину дополненного сообщения в битах
        // Сначала добавляем 1 бит, затем нули, пока не останется 8 байт (64 бита) для длины
        unsigned long long padded_message_len_bits = original_bit_len + 1; // +1 для бита '1'
        while ((padded_message_len_bits % 512) != 448) {
            padded_message_len_bits++;
        }
        padded_message_len_bits += 64; // +64 для длины сообщения

        unsigned long long total_blocks = padded_message_len_bits / 512; // Каждый блок 512 бит (64 байта)

        // Инициализация хеш-значений
        for (int i = 0; i < 8; ++i) {
            h[i] = H_initial[i];
        }

        // Обработка блоков
        unsigned int w[64]; // Расписание сообщений (для каждого блока)

        for (unsigned long long block_idx = 0; block_idx < total_blocks; ++block_idx) {
            // Чтение 64 байт текущего блока
            for (int j = 0; j < 16; ++j) {
                unsigned int current_word = 0;
                for (int byte_offset = 0; byte_offset < 4; ++byte_offset) {
                    unsigned long long current_byte_pos = block_idx * 64 + j * 4 + byte_offset;

                    unsigned char current_byte;
                    if (current_byte_pos < message_len_bytes) {
                        // Если это байт из исходного сообщения
                        current_byte = static_cast<unsigned char>(message[current_byte_pos]);
                    } else if (current_byte_pos == message_len_bytes) {
                        // Первый байт дополнения (бит '1')
                        current_byte = 0x80;
                    } else if (current_byte_pos >= (padded_message_len_bits / 8) - 8) {
                        // Последние 8 байт (64 бита) - длина исходного сообщения
                        int len_byte_idx = 7 - ( (padded_message_len_bits / 8) - 1 - current_byte_pos);
                        current_byte = static_cast<unsigned char>((original_bit_len >> (len_byte_idx * 8)) & 0xFF);
                    } else {
                        // Байты дополнения нулями
                        current_byte = 0x00;
                    }
                    current_word = (current_word << 8) | current_byte;
                }
                w[j] = current_word;
            }

            // Расширение остальных 48 слов
            for (int j = 16; j < 64; ++j) {
                w[j] = sigma1(w[j - 2]) + w[j - 7] + sigma0(w[j - 15]) + w[j - 16];
            }

            // Инициализация рабочих переменных
            unsigned int a = h[0];
            unsigned int b = h[1];
            unsigned int c = h[2];
            unsigned int d = h[3];
            unsigned int e = h[4];
            unsigned int f = h[5];
            unsigned int g = h[6];
            unsigned int hi = h[7];

            // Основной цикл компрессии (64 раунда)
            for (int j = 0; j < 64; ++j) {
                unsigned int T1 = hi + Sigma1(e) + Ch(e, f, g) + K[j] + w[j];
                unsigned int T2 = Sigma0(a) + Maj(a, b, c);

                hi = g;
                g = f;
                f = e;
                e = d + T1;
                d = c;
                c = b;
                b = a;
                a = T1 + T2;
            }

            // Добавление результатов текущего блока к хеш-значениям
            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
            h[5] += f;
            h[6] += g;
            h[7] += hi;
        }
    }

    std::string gethash() {
        std::stringstream ss;
        for (int i = 0; i < 8; ++i) {
            ss << std::hex << std::setw(8) << std::setfill('0') << h[i];
        }
        return ss.str();
    }
private:
    // Приватные вспомогательные функции
    static unsigned int rotr(unsigned int x, unsigned int n) {
        return (x >> n) | (x << (32 - n));
    }

    static unsigned int Ch(unsigned int x, unsigned int y, unsigned int z) {
        return (x & y) ^ (~x & z);
    }

    static unsigned int Maj(unsigned int x, unsigned int y, unsigned int z) {
        return (x & y) ^ (x & z) ^ (y & z);
    }

    static unsigned int Sigma0(unsigned int x) {
        return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
    }

    static unsigned int Sigma1(unsigned int x) {
        return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
    }

    static unsigned int sigma0(unsigned int x) {
        return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
    }

    static unsigned int sigma1(unsigned int x) {
        return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
    }

    // Приватные константы
    unsigned int h[8];
    static const unsigned int K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    static const unsigned int H_initial[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
};
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
    const unsigned char *buffer = dynamic_cast<const unsigned char*>(data);
    u32 crc = -1;
    while(len--) {
        crc = pow(crc, static_cast<u32>((*buffer++) << 24));
        for( int bit = 0; bit < 8; bit++ )
            crc = crc & (1L << 31) ? pow((crc << 1), POLY) : (crc << 1);
    }
    u32 res {reflect32(~crc)};
    result = &res;
    #undef POLY
    return E_EVENT_OK;
}
#endif /* __CRC_PROGRAMABLE__ */

