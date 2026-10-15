#include "types.h"

extern void * EffectResFindByName_2e2f10(s32, s32);
extern s32 EffectEntryIsLoadedByName_2de700(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x5C];
    s32 m5C;
};

s32 EffectIsLoadedByName_2dff60(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    struct Obj0 * rv1;
    s32 t0;
    s32 r2;

    r0 = EffectResFindByName_2e2f10(p0, p1);
    rv1 = (struct Obj0 *)r0;
    if (r0 != 0) {
        t0 = r0->m5C;
        if (t0 == 1) {
            return 1;
        }
        rv1 = (struct Obj0 *)1;
    }
    r2 = EffectEntryIsLoadedByName_2de700((p0 + 0x1674), p1);
    return (r2 & 0xFF);
}
