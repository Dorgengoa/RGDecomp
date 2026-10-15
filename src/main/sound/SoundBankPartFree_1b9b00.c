#include "types.h"

typedef struct B_001b9b00 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
} B_001b9b00;

typedef struct A_001b9b00 {
    u8 pad0[0x18];
    B_001b9b00 arr18[1];
    u8 pad[480 - 0x18 - 56];
} A_001b9b00;

extern A_001b9b00 D_0049EB10[];
extern void SoundBankStopAll_1bad70(s32);
extern void SoundBankPartRelease_1ba620(s32, B_001b9b00 *, s32);

void SoundBankPartFree_1b9b00(u32 key)
{
    A_001b9b00 *p1;
    B_001b9b00 *p2;
    s32 i1;
    s32 i2;
    i1 = (key >> 24) & 0xFF;
    i2 = (key >> 16) & 0xFF;
    if (i1 < 0) goto z1;
    if (i1 <= 0x10) goto g1;
z1:
    p1 = 0;
    goto s1;
g1:
    p1 = &D_0049EB10[i1];
s1:
    if (p1 == 0) return;
    if (i2 < 0) goto z2;
    if (i2 < 5) goto g2;
z2:
    p2 = 0;
    goto s2;
g2:
    p2 = &p1->arr18[i2];
s2:
    if (p2 == 0) return;
    if (p2->f0 == 0) return;
    SoundBankStopAll_1bad70(i1);
    SoundBankPartRelease_1ba620(i1, p2, 0);
    p2->f0 = 0;
    p2->f4 = 0;
    p2->f8 = 0;
    p2->fC = 0;
    p2->f10 = -1;
    p2->f30 = 0;
    p2->f20 = 0;
    p2->f18 = 0;
    p2->f1C = 0;
    p2->f24 = 0;
    p2->f34 = 0;
    p2->f14 = 0;
    p2->f28 = 0;
    p2->f2C = 0;
}
