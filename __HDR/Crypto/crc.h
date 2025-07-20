#pragma once
#include "standard.h"
#include "event.h"

template <u32 t, u32 poly, typename size>
struct Polynome { 
    static const size value = (t & (-1)) ? ((t << 1) ^ poly) : (t << 1);
};

template <u32 t, u32 poly, typename size, int i>
struct For {
    static const size value = For<Polynome<t, poly, size>::value, poly, size, i-1>::value;
}; 

template <u32 t, u32 poly, typename size>
struct For<t, poly, size, 0> {
    static const size value = Polynome<t, poly, size>::value;
};

template <u32 t, u32 poly, typename size>
struct Hash {
    static const size value = For<t, poly, size, 7>::value;
};

template<i16 r, u32 poly, typename size, i16 t>
struct Crc_table:Crc_table<r+1, poly, size, t-1> {
    size *values;
    Crc_table() {
        values[t]=Hash<t, poly, size>::value;
    }
};
template<i16 r, u32 poly, typename size>
struct Crc_table<r, poly, size, 0> {
    size values[r+1];
    Crc_table() {
        values[0]=Hash<0, poly, size>::value;
    }
    size operator[](i16 i) {
        return values[i];
    }
};

template<u32 poly, typename size>
event__e crc(size* result, u32 len, const void *data) {
    // Стандартный полином для STM32 0x04C11DB7
    Crc_table<0, poly, size, 255> crc_table;
    const unsigned char *buffer = static_cast<const unsigned char*>(data);
    size crc {-1};
    while(len--)
    if constexpr (sizeof(size) == sizeof(u8))
    // CRC8
        crc = crc_table[crc ^ *buffer++];
    else if constexpr (sizeof(size) == sizeof(u16))
    // CRC16
        crc = crc_table[(crc ^ *buffer++)] ^ (crc >> 8);
    else if constexpr (sizeof(size) == sizeof(u32))
    // CRC32
        crc = crc_table[(crc ^ *buffer++) & 0xFF] ^ (crc >> 8);
    *result = crc ^ 0xFFFFFFFFUL;
    return EVENT__OK;
}