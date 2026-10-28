/* rgp:protos */
#define RGP_SELF_EffDefCmdTexAnimeDataEnd_19dda0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

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
    u8 pad024[0x30];
    s32 m54;
};

s32 EffDefCmdTexAnimeDataEnd_19dda0(s32 p0, s32 p1, struct Obj0 *p2)
{
    struct Obj1 * t0;
    s32 t1;
    s32 rv1;
    s32 t2;
    s32 r0;

    t0 = p2->m00;
    t1 = p2->m00->m54;
    rv1 = 1;
    if (t1 == 0) {
        rv1 = 0;
    } else {
        t2 = p2->m00->m20;
        r0 = (EffTexAnimeParamBuildStepArray_198150(t1, t2), (s32)0);
        rv1 = 1;
    }
    return rv1;
}
