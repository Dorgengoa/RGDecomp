#include "types.h"

extern void GsEnvInit_1573b0(void *);
extern void MtxIdentity_13d2e0(void *);
extern void VecSetOnes_13e180(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    u8 m10;
    u8 pad011[0x3];
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    u8 pad02C[0x4];
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
};

void CameraRecInit_156940(struct Obj0 *p0)
{
    GsEnvInit_1573b0((struct Obj0 *)((u8 *)p0 + 0x50));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0xB0));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0xF0));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0x130));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0x180));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0x1C0));
    MtxIdentity_13d2e0((struct Obj0 *)((u8 *)p0 + 0x200));
    VecSetOnes_13e180((struct Obj0 *)((u8 *)p0 + 0x240));
    p0->m14 = 0;
    p0->m1C = 0;
    p0->m18 = 0;
    p0->m24 = 0;
    p0->m20 = 0;
    p0->m28 = 0;
    p0->m40 = 0x3F800000;
    p0->m3C = 0;
    p0->m38 = 0;
    p0->m34 = 0;
    p0->m30 = 0;
    p0->m44 = 0x3F400000;
    p0->m4C = 0;
    p0->m48 = 0;
    p0->m00 = 1;
    p0->m04 = 1;
    p0->m10 = 0;
}
