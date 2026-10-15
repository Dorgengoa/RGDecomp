#include "types.h"

extern s32 GetStaticScene_1c6c70(void);
extern void HeadLookUpdate_1c5460(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef unsigned __int128 u128;

struct Obj0;

struct Obj0 {
    u16 m00;
    u8 pad002[0x6E];
    s16 m70;
    u8 pad072[0xE];
    u128 m80;
    u128 m90;
    u8 pad0A0[0x24];
    s16 mC4;
};

void NpcObjHeadLookUpdate_2fc3f0(struct Obj0 *p0)
{
    u16 t0;
    s32 r0;
    s16 t1;
    u128 t2;

    t0 = p0->m00;
    if ((t0 & 1) != 0) {
        r0 = GetStaticScene_1c6c70();
        t1 = p0->mC4;
        if (t1 >= 0) {
            t2 = p0->m90;
            p0->m80 = t2;
            p0->m70 = 0;
            HeadLookUpdate_1c5460((struct Obj0 *)((u8 *)p0 + 0x10), r0);
        }
        return;
    }
}
