/* rgp:protos */
#define RGP_SELF_MapCfgPieceName_18c1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 strlen(s32);
/*rgp*/
/*rgp*/
extern s32 strcpy(s32, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481258;
extern s32 D_0048125C;

s32 MapCfgPieceName_18c1d0(s32 p0)
{
    s32 t0;
    s32 rv7;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 t1;
    s32 r4;
    s32 r5;
    s32 r6;

    t0 = D_00481258;
    rv7 = 1;
    if (t0 == 0) {
        rv7 = 0;
    } else {
        r0 = ListNodeGetData_18bff0(t0);
        r1 = SlotGetInt_15f720(p0);
        if (r1 != 0) {
            r2 = strlen(r1);
            r3 = BytesToQwords_18a6c0((r2 + 1));
            t1 = D_0048125C;
            r4 = MemStackAllocQw_14d950(t1, r3);
            r5 = ((s32)strcpy(r4, r1));
            r6 = (NodeObjBasicSetName_18c270(r0, r4), (s32)0);
        }
        rv7 = 1;
    }
    return rv7;
}
