#include "types.h"

typedef unsigned __int128 u128;

extern void MatZero_13d2c0(void *arg0);

void LightStateInit_156b50(void *arg0) {
    s32 temp_3;
    s32 i;
    u8 *rec;

    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    *(u128 *)((u8 *)arg0 + 0x10) = 0;
    *(u32 *)((u8 *)arg0 + 0x1C) = 0x43000000;
    MatZero_13d2c0((u8 *)arg0 + 0x20);
    MatZero_13d2c0((u8 *)arg0 + 0x60);
    *(u128 *)((u8 *)arg0 + 0xA0) = 0;
    *(u32 *)((u8 *)arg0 + 0xCC) = 0x43000000;
    *(u32 *)((u8 *)arg0 + 0xC8) = 0x43000000;
    i = 0;
    *(u32 *)((u8 *)arg0 + 0xC4) = 0x43000000;
    *(u32 *)((u8 *)arg0 + 0xC0) = 0x43000000;
    *(u128 *)((u8 *)arg0 + 0xD0) = *(u128 *)((u8 *)arg0 + 0xC0);
    *(u32 *)((u8 *)arg0 + 0xBC) = 0x437F0000;
    *(u32 *)((u8 *)arg0 + 0xB8) = 0x437F0000;
    *(u32 *)((u8 *)arg0 + 0xB4) = 0x437F0000;
    *(u32 *)((u8 *)arg0 + 0xB0) = 0x437F0000;
    do {
        temp_3 = i * 0x30;
        i += 1;
        rec = (u8 *)arg0 + temp_3;
        *(u32 *)(rec + 0x100) = 0xBF800000;
        *(u128 *)(rec + 0xF0) = 0;
        *(u128 *)(rec + 0xE0) = 0;
    } while (i < 4);
}
