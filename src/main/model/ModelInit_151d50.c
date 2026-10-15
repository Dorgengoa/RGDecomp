#include "types.h"
#pragma vu0_mmi_reg_binding on
extern __int128 vz151d50 asm("vf0");

typedef struct Obj151d50 {
    s32 x0;
    s32 x4;
    u8 pad8[0xF8];
    s32 x100;
    void *x104;
    s32 x108;
    s32 n10C;
    s32 *x110;
    u8 pad114[0xC];
    s32 x120;
    s32 x124;
    s32 x128;
    s32 x12C;
    s32 x130;
    u8 pad134[0x2C];
    s32 x160;
    s32 x164;
    u8 pad168[0x8];
    f32 x170;
    u8 pad174[0xC];
    __int128 v180;
    union {
        __int128 q;
        struct { s32 x, y, z, w; } s;
    } v190;
    u8 sub1A0[0x10];
} Obj151d50;

extern void VecSetOnes_13e180(void *p);
extern void *ArrayGetChecked_152fd0(void *a, s32 b);
extern void FrameSetDirty_14a5e0(void *p);

void ModelInit_151d50(Obj151d50 *p)
{
    s32 i;
    Obj151d50 *s;

    s = p;
    p->x0 = 0;
    p->x4 = 0;
    p->x100 = 0;
    p->x104 = 0;
    p->x124 = 0;
    p->x128 = 0;
    p->x12C = 0;
    p->x120 = 0;
    p->x164 = 0;
    p->x130 = 0;
    p->x160 = 0;
    p->n10C = 0;
    p->x110 = 0;
    p->x108 = 0;
    p->x170 = 1.0f;
    if (p) { p = (Obj151d50 *)(s32)(u32)p; }
    s->v180 = vz151d50;
    s->v190.q = 0;
    p->v190.s.w = 1;
    VecSetOnes_13e180(s->sub1A0);
    for (i = 0; i < s->n10C; i++) {
        p = ArrayGetChecked_152fd0(s->x104, s->x110[i]);
        if (p) {
            FrameSetDirty_14a5e0(p);
        }
    }
}
