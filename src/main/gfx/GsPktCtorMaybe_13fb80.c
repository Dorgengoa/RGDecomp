#include "types.h"

extern s32 NameTableNodeCtor_15ae50(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x6C];
    s64 m70;
    u8 pad078[0x68];
    s32 mE0;
    s32 mE4;
    s32 mE8;
    u8 pad0EC[0x24];
    s32 m110;
    u8 pad114[0x8];
    s32 m11C;
    s32 m120;
    s32 m124;
};

struct Obj0 *GsPktCtorMaybe_13fb80(struct Obj0 *p0)
{
    s32 r0;

    r0 = NameTableNodeCtor_15ae50((struct Obj0 *)((u8 *)p0 + 0x78));
    p0->m00 = 0;
    p0->mE8 = 1;
    p0->m110 = 0x3F800000;
    p0->m70 = 0x100;
    p0->mE0 = 1;
    p0->mE4 = 0;
    p0->m11C = 0;
    p0->m124 = 0;
    p0->m120 = 0;
    return p0;
}
