/* rgp:protos */
#define RGP_SELF_CharaResReleaseById_1f1160 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0xD00];
    s32 mD00;
};

s32 CharaResReleaseById_1f1160(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 t0;

    r0 = CharaResFindById_1f0530(p0, p2);
    if (r0 != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        t0 = p0->mD00;
        CharaResRecRelease_1f4510(r0, p1, t0);
    }
}
