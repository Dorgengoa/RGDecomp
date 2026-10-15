#include "types.h"

extern s32 ListNodeGetData_18bff0(s32);
extern void VariantReadVec3_15f6c0(void *, s32);
extern s32 NodeSetRotation_186620(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481258;

s32 MapCfgPieceRot_18c0f0(s32 p0)
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
            r2 = NodeSetRotation_186620(r0, &v30);
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
