#include "types.h"

extern s32 MesWinCalcCharWaitFrames_24e270(s32);
extern s32 MesWinPageCharCount_24e350(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0x4];
    s32 m14;
    s32 m18;
};

s32 MesWinOwnerCalcPageWait_24e860(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 t2;
    s32 r1;

    t0 = p0->m0C;
    r0 = MesWinCalcCharWaitFrames_24e270(t0);
    t1 = p0->m0C;
    t2 = p0->m14;
    r1 = MesWinPageCharCount_24e350(t1, t2);
    if (r1 < 0) {
        p0->m18 = -1;
        return r1;
    }
    p0->m18 = (r1 * r0);
    return r1;
}
