#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetPsmBpp_145140(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

struct Obj2 {
    s32 m00;
};

s32 DrawEnvGetScreenInfo_289a40(s32 p0, struct Obj0 *p1, struct Obj1 *p2, struct Obj2 *p3)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = GetDrawCtx_15de80();
    if (r0 == 0) {
        return 0;
    }
    r1 = DrawEnvGetWidth_1451e0(r0);
    p1->m00 = r1;
    r2 = DrawEnvGetHeight_1451d0(r0);
    p2->m00 = r2;
    r3 = DrawEnvGetPsmBpp_145140(r0);
    p3->m00 = r3;
    return 1;
}
