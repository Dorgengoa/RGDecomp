#include "types.h"

extern s32 SceneTreeBuildIndex_19aca0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    struct Obj1 *m00;
};

struct Obj1 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
};

s32 EffDefCmdEffFrameHierarchyEnd_19b7b0(s32 p0, s32 p1, struct Obj0 *p2)
{
    struct Obj1 * t0;
    s32 t1;
    s32 t2;
    s32 r0;

    t0 = p2->m00;
    t1 = p2->m00->m20;
    t2 = p2->m00->m24;
    r0 = SceneTreeBuildIndex_19aca0(t2, t1);
    return 1;
}
