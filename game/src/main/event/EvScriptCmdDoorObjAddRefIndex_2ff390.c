/* rgp:protos */
#define RGP_SELF_EvScriptCmdDoorObjAddRefIndex_2ff390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482850;
extern s32 D_00482854;

s32 EvScriptCmdDoorObjAddRefIndex_2ff390(s32 p0, s32 p1)
{
    s32 t0;
    s32 l0;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 t3;
    s32 t4;

    t0 = D_00482850;
    if (t0 == 0) {
        return 1;
    }
    l0 = 0;
    while (l0 < p1) {
        t1 = D_00482854;
        if (t1 >= 0x40) {
            break;
        }
        r1 = ScriptArgGetAreaId_3019b0((p0 + (l0 << 3)));
        t2 = D_00482854;
        t3 = D_00482850;
        *(s16 *)((u8 *)t3 + (t2 << 1)) = r1;
        t4 = D_00482854;
        D_00482854 = (t4 + 1);
        l0 = (l0 + 1);
    }
    return 1;
}
