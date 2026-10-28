/* rgp:protos */
#define RGP_SELF_ModelApplyMotionKeys_150650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x104];
    s32 m104;
    u8 pad108[0x20];
    s32 m128;
};

s32 ModelApplyMotionKeys_150650(struct Obj0 *p0, s32 p1, f32 fa0)
{
    s32 rv2;
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;

    rv2 = (r0 | r1);
    if (p1 == 0) {
        rv2 = 0;
    } else {
        t0 = p0->m128;
        r0 = AnimApplyMaterialKeys_154200(t0, p1, fa0);
        t1 = p0->m104;
        r1 = AnimApplyFrameKeys_1542d0(t1, p1, fa0);
        rv2 = (r0 | r1);
    }
    return rv2;
}
