#include "types.h"

extern s32 TargetRefGetKind_2e7130(void *);
extern s32 GetMapMgr_201a90(void);
extern s32 MapSetDataFlag2ById_1e4da0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

s32 TargetRefSetAreaFlag2_2e6790(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    s16 t0;
    s32 r2;

    r0 = TargetRefGetKind_2e7130(p0);
    if (r0 != 0xA && r0 != 9 && r0 != 8 && r0 != 7 && r0 != 6) {
        return r0;
    }
    r1 = GetMapMgr_201a90();
    t0 = p0->m02;
    r2 = MapSetDataFlag2ById_1e4da0(r1, t0, 1);
    return r2;
}
