/* rgp:protos */
#define RGP_SELF_MinimapSetScreenAnchorPos_324ca0 1
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
    u8 pad000[0x10E];
    s16 m10E;
    s16 m110;
};

s32 MinimapSetScreenAnchorPos_324ca0(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv3;
    s32 rv4;

    r0 = GetDrawCtx_15de80();
    r1 = DrawEnvGetWidth_1451e0(r0);
    r2 = DrawEnvGetHeight_1451d0(r0);
    rv3 = p1;
    if (p1 == -1) {
        rv3 = (r1 + -0xD2);
    }
    rv4 = p2;
    if (p2 == -1) {
        rv4 = (r2 + -0xB2);
    }
    p0->m10E = rv3;
    p0->m110 = rv4;
    return r2;
}
