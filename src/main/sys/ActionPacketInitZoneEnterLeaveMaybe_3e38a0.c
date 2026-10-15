#include "types.h"

extern void ActionPacketClear_3e3e90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483994;

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 m02;
    u8 m03;
    u8 pad004[0x8];
    s32 m0C;
    s32 m10;
};

struct Obj0 *ActionPacketInitZoneEnterLeaveMaybe_3e38a0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 rv1;

    t0 = D_00483994;
    if (t0 == 0) {
        return (struct Obj0 *)0;
    }
    ActionPacketClear_3e3e90(p0);
    rv1 = 0xE;
    if (p3 != 0) {
        p0->m02 = 4;
        rv1 = 4;
    } else {
        p0->m02 = 0xE;
        rv1 = 0xE;
    }
    p0->m03 = 0x19;
    p0->m00 = 2;
    p0->m0C = p1;
    p0->m10 = p2;
    return p0;
}
