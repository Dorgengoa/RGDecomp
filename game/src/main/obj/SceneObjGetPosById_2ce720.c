/* rgp:protos */
#define RGP_SELF_SceneObjGetPosById_2ce720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x180];
    u128 m180;
};

struct Obj1 {
    u128 m00;
};

s32 SceneObjGetPosById_2ce720(s32 p0, s32 p1, struct Obj1 *p2)
{
    struct Obj0 *r0;
    s32 r1;
    s32 r2;
    u128 t0;

    r0 = ObjRecGetLiveObject_1c4a90(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    r1 = ModelGetRootFrame_1511a0(r0);
    if (r1 != 0) {
        r2 = (FrameGetWorldPos_148f30(r1, p2), (s32)0);
    } else {
        t0 = r0->m180;
        p2->m00 = t0;
    }
    return 1;
}
