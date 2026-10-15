#include "types.h"

extern void TargetRefResolve_2e5ed0(void *, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern s32 ModelGetFrame_1511f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
    s32 m34;
};

struct Obj1 {
    u8 pad000[0x6C];
    s32 m6C;
};

void EvTargetBindNode_3526d0(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 t1;
    s32 r1;
    s32 r2;

    TargetRefResolve_2e5ed0(p0, 0);
    p0->m34 = 0;
    if (p1 != 0) {
        t0 = p0->m30;
        if (t0 == 0) {
            return;
        }
        t1 = p1->m6C;
        r1 = ModelFindFrameIndexByName_151220(t1, t0);
        r2 = ModelGetFrame_1511f0(t1, r1);
        p0->m34 = r2;
        return;
    }
}
