/* rgp:protos */
#define RGP_SELF_EvCmdInsectPowerTalkIdGetMaybe_25ee00 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 EvCmdInsectPowerTalkIdGetMaybe_25ee00(s32 p0, s32 p1)
{
    s32 rv5;
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 rv3;
    s32 r2;
    s32 r4;

    rv5 = 1;
    if (p1 != 1) {
        rv5 = 0;
    } else {
        r0 = GetGameData_1fede0();
        t0 = r0->m10;
        r1 = ((short)StateVarGet_3ccac0(t0, 0x1A));
        rv3 = r2;
        if (r1 > 0) {
            rv3 = (r1 + -1);
        } else {
            r2 = InsectBattlePickPowerTalkIdMaybe_319720();
            rv3 = r2;
        }
        r4 = (ScriptSetRefInt_26a1e0(p0, rv3), (s32)0);
        rv5 = 1;
    }
    return rv5;
}
