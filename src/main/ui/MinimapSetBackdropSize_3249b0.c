#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x100];
    s16 m100;
    s16 m102;
};

s32 MinimapSetBackdropSize_3249b0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetDrawCtx_15de80();
    r1 = DrawEnvGetWidth_1451e0(r0);
    r2 = DrawEnvGetHeight_1451d0(r0);
    p0->m100 = p1;
    p0->m102 = p2;
    if (p1 == -1) {
        p0->m100 = r1;
    }
    if (p2 == -1) {
        p0->m102 = r2;
    }
    return r2;
}
