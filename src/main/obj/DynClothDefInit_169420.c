#include "types.h"
typedef unsigned __int128 u128;

extern s32 Rand_133710(void);
extern void MtxIdentity_13d2e0(void *);
extern const f32 D_0047D270 __attribute__((section(".sdata")));
extern const f32 D_0047D274 __attribute__((section(".sdata")));

void DynClothDefInit_169420(void *arg0)
{
    *(s32 *)((u8 *)arg0 + 0x0) = 1;
    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    MtxIdentity_13d2e0((u8 *)arg0 + 0x10);
    MtxIdentity_13d2e0((u8 *)arg0 + 0x50);
    *(s32 *)((u8 *)arg0 + 0x90) = 0;
    *(s32 *)((u8 *)arg0 + 0x94) = 0;
    *(s32 *)((u8 *)arg0 + 0x98) = 0;
    *(s32 *)((u8 *)arg0 + 0x9C) = 0;
    *(s32 *)((u8 *)arg0 + 0xA0) = 0;
    *(s32 *)((u8 *)arg0 + 0xA4) = 0;
    *(s32 *)((u8 *)arg0 + 0xA8) = 0;
    *(s32 *)((u8 *)arg0 + 0xAC) = 0;
    *(s32 *)((u8 *)arg0 + 0xB0) = 0;
    *(s32 *)((u8 *)arg0 + 0xB8) = 0;
    *(s32 *)((u8 *)arg0 + 0xBC) = 0;
    *(s32 *)((u8 *)arg0 + 0xC0) = 0;
    *(s32 *)((u8 *)arg0 + 0xC4) = 0;
    *(s32 *)((u8 *)arg0 + 0xC8) = 0;
    *(s32 *)((u8 *)arg0 + 0xCC) = 0;
    *(s32 *)((u8 *)arg0 + 0xD0) = 0;
    *(s32 *)((u8 *)arg0 + 0xD4) = 0;
    *(s32 *)((u8 *)arg0 + 0xD8) = 0;
    *(s32 *)((u8 *)arg0 + 0xDC) = 0;
    *(s32 *)((u8 *)arg0 + 0xE0) = 0;
    *(s32 *)((u8 *)arg0 + 0xE4) = 0;
    *(s32 *)((u8 *)arg0 + 0xE8) = 0;
    *(s32 *)((u8 *)arg0 + 0xEC) = 0;
    *(s32 *)((u8 *)arg0 + 0xF0) = 0;
    *(u128 *)((u8 *)arg0 + 0x100) = 0;
    *(f32 *)((u8 *)arg0 + 0x104) = D_0047D270;
    *(s32 *)((u8 *)arg0 + 0x110) = 0;
    *(f32 *)((u8 *)arg0 + 0x114) = D_0047D274;
    *(s32 *)((u8 *)arg0 + 0xF4) = 6;
    *(s32 *)((u8 *)arg0 + 0xF8) = 0;
    *(s32 *)((u8 *)arg0 + 0x118) = 0;
    *(s32 *)((u8 *)arg0 + 0x120) = 0;
    *(u128 *)((u8 *)arg0 + 0x130) = 0;
    *(s32 *)((u8 *)arg0 + 0x140) = Rand_133710();
    *(s32 *)((u8 *)arg0 + 0x144) = 0;
    *(f32 *)((u8 *)arg0 + 0x11C) = 1.0f;
    *(s32 *)((u8 *)arg0 + 0x148) = 0;
    *(f32 *)((u8 *)arg0 + 0x14C) = -100000;
    *(s32 *)((u8 *)arg0 + 0x150) = 1;
    *(u128 *)((u8 *)arg0 + 0x160) = 0;
    *(s32 *)((u8 *)arg0 + 0x154) = 0;
}
