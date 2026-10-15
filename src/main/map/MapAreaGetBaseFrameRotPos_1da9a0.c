#include "types.h"

extern s32 MapAreaFindBaseFrameByName_1daa30(s32, s32);
extern s32 FrameCalcWorldMatrix_148ff0(s32, void *);
extern s32 MatToRotPos_1cade0(void *, void *, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

s32 MapAreaGetBaseFrameRotPos_1da9a0(s32 p0, struct Obj0 *p1, struct Obj1 *p2, s32 p3)
{
    u128 v30[4];
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = MapAreaFindBaseFrameByName_1daa30(p0, p3);
    rv3 = 0;
    if (r0 != 0) {
        r1 = FrameCalcWorldMatrix_148ff0(r0, v30);
        r2 = MatToRotPos_1cade0(p1, p2, v30);
        rv3 = 1;
    } else {
        p1->m00 = 0;
        p1->m04 = 0;
        p1->m08 = 0;
        p1->m0C = 0x3F800000;
        p2->m00 = 0;
        p2->m04 = 0;
        p2->m08 = 0;
        p2->m0C = 0x3F800000;
        rv3 = 0;
    }
    return rv3;
}
