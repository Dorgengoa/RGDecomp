/* rgp:protos */
#define RGP_SELF_EvCmdMapAreaCallScript_246af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
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
    s32 m00;
};

s32 EvCmdMapAreaCallScript_246af0(struct Obj0 *p0, s32 p1)
{
    s32 rv7;
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;

    rv7 = 1;
    if (p1 != 2) {
        rv7 = 0;
    } else {
        r0 = ((s32)GetMapMgr_201a90());
        t0 = p0->m00;
        if (t0 == 2) {
            r1 = ScriptGetCodeAddr_249050(p0);
            r2 = ScriptGetInt_2490f0((struct Obj0 *)((u8 *)p0 + 8));
            r3 = MapAreaCallScript_1e4370(r0, r1, r2);
        } else {
            r4 = ScriptGetInt_2490f0(p0);
            r5 = ScriptGetInt_2490f0((struct Obj0 *)((u8 *)p0 + 8));
            r6 = MapAreaCallScriptById_1e43b0(r0, r4, r5);
        }
        rv7 = 1;
    }
    return rv7;
}
