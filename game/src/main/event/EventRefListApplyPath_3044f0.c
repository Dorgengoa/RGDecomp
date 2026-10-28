/* rgp:protos */
#define RGP_SELF_EventRefListApplyPath_3044f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

u8 EventRefListApplyPath_3044f0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 vD0[3];
    u128 v90[4];
    u128 v80;
    u128 v70;
    u128 v60;
    s32 t0;
    s32 t1;
    u8 r1;
    s32 l4;
    s32 t2;
    s32 t3;

    t0 = p0->m00;
    if (t0 == 0) {
        return 0;
    }
    SrtCtor48_1c7510(vD0);
    t1 = p0->m00;
    r1 = EventPathEvalXformByName_2e3d20(t1, vD0, p2, p3, p4);
    SrtMatMul_1c7470(vD0, v90, p1);
    MatDecomposeScaleRotPos_1cad20(&v80, &v70, &v60, v90);
    l4 = 0;
    while (l4 < p0->m08) {
        t2 = p0->m04;
        TargetRefDetachFromParent_2e5890((t2 + ((l4 * 3) << 4)));
        t3 = p0->m04;
        TargetRefSetScaleRotPos_2e5a50((t3 + ((l4 * 3) << 4)), &v80, &v70, &v60);
        l4 = (l4 + 1);
    }
    return r1;
}
