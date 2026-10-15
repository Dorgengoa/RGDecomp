#include "types.h"

typedef unsigned __int128 u128;

extern void MtxIdentity_13d2e0(void *p);

void CameraBaseInit_15fc80(u8 *p)
{
    *(f32 *)(p + 0x00) = 45.0f;
    MtxIdentity_13d2e0(p + 0x10);
    *(s32 *)(p + 0x70) = 0;
    *(u128 *)(p + 0x50) = 0;
    *(u128 *)(p + 0x60) = 0;
    *(f32 *)(p + 0x68) = -1.0f;
    MtxIdentity_13d2e0(p + 0x80);
}
