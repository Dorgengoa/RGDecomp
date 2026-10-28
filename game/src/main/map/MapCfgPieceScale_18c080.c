/* rgp:protos */
#define RGP_SELF_MapCfgPieceScale_18c080 1
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

extern s32 D_00481258;

s32 MapCfgPieceScale_18c080(s32 p0)
{
    u128 v30;
    s32 t0;
    s32 rv4;
    s32 r0;
    s32 rv3;
    s32 r2;

    t0 = D_00481258;
    if (t0 == 0) {
        rv4 = 0;
    } else {
        r0 = ListNodeGetData_18bff0(t0);
        rv3 = 1;
        if (r0 == 0) {
            rv3 = 0;
        } else {
            VariantReadVec3_15f6c0(&v30, p0);
            r2 = (NodeSetScale_1865b0(r0, &v30), (s32)0);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
