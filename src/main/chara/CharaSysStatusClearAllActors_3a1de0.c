#include "types.h"

extern s32 CharaMgrPoolStatusClearAll_3a8960(s32, s32, s32, s32);
extern s32 ObjMgrStatusClearAll_3bab20(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004837C0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x4];
    s32 m1C;
};

s32 CharaSysStatusClearAllActors_3a1de0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 t1;
    s32 r0;
    s32 t3;
    s32 r1;

    t1 = D_004837C0->m14;
    r0 = CharaMgrPoolStatusClearAll_3a8960(t1, p1, p2, p3);
    t3 = D_004837C0->m1C;
    r1 = ObjMgrStatusClearAll_3bab20(t3, p1, p2, p3);
    return 1;
}
