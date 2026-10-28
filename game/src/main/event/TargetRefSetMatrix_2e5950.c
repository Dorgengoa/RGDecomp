/* rgp:protos */
#define RGP_SELF_TargetRefSetMatrix_2e5950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

void TargetRefSetMatrix_2e5950(struct Obj0 *p0, s32 p1)
{
    u128 v50;
    u128 v40;
    u128 v30;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = ((short)TargetRefGetKind_2e7130(p0));
    if (r0 != 1) {
        t0 = p0->m04;
        if (t0 == 0) {
            return;
        }
    }
    r1 = (MatDecomposeScaleRotPos_1cad20(&v50, &v40, &v30, p1), (s32)0);
    r2 = (TargetRefSetScaleRotPos_2e5a50(p0, &v50, &v40, &v30), (s32)0);
}
