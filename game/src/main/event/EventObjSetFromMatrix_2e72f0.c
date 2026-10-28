/* rgp:protos */
#define RGP_SELF_EventObjSetFromMatrix_2e72f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int EventObjSetFromMatrix_2e72f0(s32 p0, s32 p1)
{
    u128 v40;
    u128 v30;
    u128 v20;

    MatDecomposeScaleRotPos_1cad20(&v40, &v30, &v20, p1);
    EventObjSetScale_2e72e0(p0, &v40);
    EventObjSetRot_2e7240(p0, &v30);
    return EventObjSetPos_2e7230(p0, &v20);
}
