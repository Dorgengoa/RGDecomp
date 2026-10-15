#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 TexAnimeTableApplyMaybe_162f50(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x4];
    s32 m0C;
    u8 pad010[0x4];
    s32 m14;
};

void EffTexResApplyAnimMaybe_1a8410(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 r0;
    s32 t2;
    s32 t3;
    s32 r1;

    t0 = p0->m14;
    if (p1 != t0) {
        p0->m14 = p1;
        t1 = p0->m0C;
        if (t1 == 0) {
            return;
        }
        r0 = GetDrawCtx_15de80();
        t2 = p0->m0C;
        t3 = p0->m04;
        r1 = TexAnimeTableApplyMaybe_162f50(t2, r0, t3);
        return;
    }
}
