/* rgp:protos */
#define RGP_SELF_MinimapMgrUpdate_322030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x510];
    s32 m510;
    s32 m514;
};

s32 MinimapMgrUpdate_322030(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 r3;
    s32 rv5;
    s32 t3;
    s32 r4;
    s32 r6;
    s32 r7;

    t0 = p0->m510;
    if (t0 != 0) {
        r0 = MinimapSlotIsActive_322510(t0);
        rv2 = r0;
        if (r0 != 0) {
            t1 = p0->m510;
            r1 = (MinimapUpdate_3295a0(t1, p1), (s32)0);
            rv2 = r1;
        }
    }
    t2 = p0->m514;
    if (t2 != 0) {
        r3 = MinimapSlotIsActive_322510(t2);
        rv5 = 0;
        if (r3 != 0) {
            t3 = p0->m514;
            r4 = (MinimapUpdate_3295a0(t3, p1), (s32)0);
            rv5 = r4;
        }
    }
    r6 = (MinimapMgrFadeStep_321d60(p0), (s32)0);
    r7 = (MinimapMgrFinishTransition_321c80(p0), (s32)0);
    return r7;
}
