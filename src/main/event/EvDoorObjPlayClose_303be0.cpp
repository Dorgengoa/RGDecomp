#include "types.h"

struct C220 {
    u8 pad000[0xDC];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2(s32);
};

extern "C" void strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_004621E0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xD0];
    s32 mD0;
    u8 pad0D4[0xC8];
    s16 m19C;
    s16 m19E;
    u8 pad1A0[0x1];
    u8 m1A1;
    u8 m1A2;
};

extern "C" void EvDoorObjPlayClose_303be0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    bool ok;

    if (p1 != 0) {
        t0 = p0->mD0;
        ok = !(t0 & 0x80000000);
        if (!ok) {
            return;
        }
    }
    p0->m19E = 0;
    strcpy((struct Obj0 *)((u8 *)p0 + 0x18C), D_004621E0);
    p0->m19C = 3;
    p0->m1A2 = 1;
    p0->m1A1 = 0;
    ((struct C220 *)p0)->v2(0);
}
