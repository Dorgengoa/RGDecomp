/* rgp:protos */
#define RGP_SELF_EvScriptCmdObjAreaFadeCreate_300620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
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

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdObjAreaFadeCreate_300620(s32 p0, s32 p1)
{
    u128 v50[15];
    s32 r0;
    s32 rv8;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 t0;
    s32 t1;
    s32 r7;

    r0 = (EvScriptTemplatesReset_301c20(), (s32)0);
    rv8 = 1;
    if (p1 != 4) {
        rv8 = 0;
    } else {
        r1 = ScriptArgGetStr_301a00(p0);
        r2 = ScriptArgGetAreaId_3019b0((p0 + 8));
        r3 = ScriptArgGetStr_301a00((p0 + 0x10));
        r4 = ScriptArgGetAreaId_3019b0((p0 + 0x18));
        r5 = ((s32)EvObjAreaFadeCtorWithKey_2f90e0(v50, r1, 0, r2, r3, r4));
        r6 = ((s32)GetEventObjMgr_2d1960());
        t0 = D_0047F0C0;
        t1 = D_0047F0C4;
        r7 = EventObjMgrCreateAreaFade_2ea0f0(r6, t0, t1, v50);
        rv8 = 1;
    }
    return rv8;
}
