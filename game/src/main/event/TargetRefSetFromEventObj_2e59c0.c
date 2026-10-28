/* rgp:protos */
#define RGP_SELF_TargetRefSetFromEventObj_2e59c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
    u8 pad000[0x4];
    s32 m04;
};

void TargetRefSetFromEventObj_2e59c0(struct Obj0 *p0, s32 p1)
{
    u128 v50;
    u128 v40;
    u128 v30;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    if (p1 != 0) {
        r0 = ((short)TargetRefGetKind_2e7130(p0));
        if (r0 != 1) {
            t0 = p0->m04;
            if (t0 == 0) {
                return;
            }
        }
        r1 = (EventObjGetScale_2e7690(p1, &v50), (s32)0);
        r2 = (EventObjGetRot_2e7670(p1, &v40), (s32)0);
        r3 = (EventObjGetPos_2e7640(p1, &v30), (s32)0);
        r4 = (TargetRefSetScaleRotPos_2e5a50(p0, &v50, &v40, &v30), (s32)0);
        return;
    }
}
