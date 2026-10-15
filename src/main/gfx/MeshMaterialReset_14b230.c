#include "types.h"
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz14b230 asm("vf0");

void MeshMaterialReset_14b230(u8 *p)
{
    *(s16 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x0) = 0;
    *(s32 *)(p + 0xC) = 0;
    *(s8 *)(p + 0x6) = 0;
    *(s16 *)(p + 0x8) = 0;
    *(s16 *)(p + 0xA) = 0;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(__int128 *)(p + 0x20) = vz14b230;
    *(u128 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x14) = 0;
}
