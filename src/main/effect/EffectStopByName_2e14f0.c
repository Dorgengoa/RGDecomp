#include "types.h"

extern void * EffectResFindByName_2e2f10(s32, s32);
extern s32 EffDefUnlinkByHandle_1a0040(s32, s32);
extern s32 EffectEntriesReleaseAllNodesByName_2de2e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

s32 EffectStopByName_2e14f0(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s32 rv3;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = EffectResFindByName_2e2f10(p0, p1);
    rv3 = r2;
    if (r0 != 0) {
        t0 = r0->m04;
        r1 = EffDefUnlinkByHandle_1a0040((p0 + 0x58), t0);
        rv3 = r1;
    } else {
        r2 = EffectEntriesReleaseAllNodesByName_2de2e0((p0 + 0x1674), p1);
        rv3 = r2;
    }
    return rv3;
}
