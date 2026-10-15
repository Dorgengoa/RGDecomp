#include "types.h"

extern s32 GetLiveObjById_1ce420(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
};

s32 NodeRefFindFrameIndex_319240(struct Obj0 *p0)
{
    s16 t0;
    s16 t1;
    s32 r0;
    s32 r1;

    t0 = p0->m00;
    t1 = p0->m02;
    r0 = GetLiveObjById_1ce420(t0, t1);
    if (r0 != 0) {
        r1 = ModelFindFrameIndexByName_151220(r0, (struct Obj0 *)((u8 *)p0 + 8));
        return r1;
    }
    return -1;
}
