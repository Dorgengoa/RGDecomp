#include "types.h"

/* the lui/dsll32/pcpyld/sd at 0x22518C is a single 64-bit constant store:
   word 0 = 0, word 1 = 0x80000000. */

extern void Zero4Bytes_303100(void *p);
extern void DListInit_42eae0(void *p);

void ActCfgTableReset_225160(void *p)
{
    u8 *q = (u8 *)p;

    *(s32 *)(q + 0x18) = 0;
    *(s32 *)(q + 0x14) = 0;
    *(s16 *)(q + 0x12) = -1;
    Zero4Bytes_303100(q + 0x1C);
    *(u64 *)(q + 0x0) = 0x8000000000000000ULL;
    *(s16 *)(q + 0x10) = 0;
    *(s32 *)(q + 0x8) = 0;
    *(f32 *)(q + 0xC) = 1.0f;
    *(s16 *)(q + 0x7A) = 0;
    *(s32 *)(q + 0x20) = 0;  *(s16 *)(q + 0x5C) = 0;
    *(s32 *)(q + 0x24) = 0;  *(s16 *)(q + 0x5E) = 0;
    *(s32 *)(q + 0x28) = 0;  *(s16 *)(q + 0x60) = 0;
    *(s32 *)(q + 0x2C) = 0;  *(s16 *)(q + 0x62) = 0;
    *(s32 *)(q + 0x30) = 0;  *(s16 *)(q + 0x64) = 0;
    *(s32 *)(q + 0x34) = 0;  *(s16 *)(q + 0x66) = 0;
    *(s32 *)(q + 0x38) = 0;  *(s16 *)(q + 0x68) = 0;
    *(s32 *)(q + 0x3C) = 0;  *(s16 *)(q + 0x6A) = 0;
    *(s32 *)(q + 0x40) = 0;  *(s16 *)(q + 0x6C) = 0;
    *(s32 *)(q + 0x44) = 0;  *(s16 *)(q + 0x6E) = 0;
    *(s32 *)(q + 0x48) = 0;  *(s16 *)(q + 0x70) = 0;
    *(s32 *)(q + 0x4C) = 0;  *(s16 *)(q + 0x72) = 0;
    *(s32 *)(q + 0x50) = 0;  *(s16 *)(q + 0x74) = 0;
    *(s32 *)(q + 0x54) = 0;  *(s16 *)(q + 0x76) = 0;
    *(s32 *)(q + 0x58) = 0;  *(s16 *)(q + 0x78) = 0;
    DListInit_42eae0(q + 0x7C);
    DListInit_42eae0(q + 0x8C);
}
