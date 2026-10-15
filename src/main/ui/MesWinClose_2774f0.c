#include "types.h"

extern s32 MesWinIsActive_2774d0(void *);
extern s32 MesWinSetFlush_2775f0(void *, s32);
extern s32 MesWinSetNameShown_271390(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x194C];
    s32 m194C;
    s32 m1950;
};

s32 MesWinClose_2774f0(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = MesWinIsActive_2774d0(p0);
    if (r0 != 0) {
        r1 = MesWinSetFlush_2775f0(p0, 0);
        p0->m194C = -1;
        p0->m1950 = 0;
    }
    r2 = MesWinSetNameShown_271390(p0, 0);
    return r2;
}
