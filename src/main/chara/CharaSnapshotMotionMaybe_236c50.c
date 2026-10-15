#include "types.h"

extern s32 ModelSetPos_151110(s32, void *);
extern s32 ModelObjGetMotionName_1add90(s32);
extern f32 ModelObjGetMotionPhase_1add70(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3F4];
    s32 m3F4;
    f32 m3F8;
    f32 m3FC;
    s32 m400;
    s32 m404;
};

void CharaSnapshotMotionMaybe_236c50(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s32 t1;
    f32 t2;
    s32 t3;
    s32 r1;
    s32 t4;
    f32 r2;

    t0 = p0->m3F4;
    if (t0 != 0) {
        r0 = ModelSetPos_151110(t0, (struct Obj0 *)((u8 *)p0 + 0x70));
        t1 = p0->m404;
        p0->m400 = t1;
        t2 = p0->m3FC;
        p0->m3F8 = t2;
        t3 = p0->m3F4;
        r1 = ModelObjGetMotionName_1add90(t3);
        p0->m404 = r1;
        t4 = p0->m3F4;
        r2 = ModelObjGetMotionPhase_1add70(t4);
        p0->m3FC = r2;
        return;
    }
}
