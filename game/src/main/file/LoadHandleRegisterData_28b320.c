/* rgp:protos */
#define RGP_SELF_LoadHandleRegisterData_28b320 1
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

s32 LoadHandleRegisterData_28b320(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 v6C;
    s32 r0;
    s32 rv5;
    s32 rv4;
    s32 r1;
    s32 t0;
    s32 r3;

    r0 = GetDrawCtxNameTable_15de40();
    if (r0 == 0) {
        return 1;
    }
    if (p3 == 0) {
        rv5 = 2;
    } else {
        rv4 = 0;
        if (p1 == 0) {
            rv4 = 3;
        } else {
            r1 = LoadHandleGetData_28b270(p0, &v6C);
            t0 = v6C;
            MemMoveIfDiff_289c60(r1, t0, p1);
            r3 = NameTableRegisterImArchive_1594d0(r0, p1, p2, p3, 0);
            rv4 = 0;
        }
        rv5 = rv4;
    }
    return rv5;
}
