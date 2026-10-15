#include "types.h"

s32 Crc16Ccitt_42f000(u8 *data, u32 len)
{
    u32 i;
    u32 bit;
    u32 crc;

    crc = 0xFFFF;
    for (i = 0; i < len; i++) {
        crc ^= data[i] << 8;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }
    return ~crc & 0xFFFF;
}
