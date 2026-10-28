/* rgp:protos */
#define RGP_SELF_EvScriptCmdM05ChangeRegister_2fdcc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F0C0;
extern s32 D_0047F0C4;
extern s32 D_00482894;
extern u8 D_004E7110[];

s32 EvScriptCmdM05ChangeRegister_2fdcc0(s32 p0, s32 p1)
{
    s32 rv3;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 t2;
    s32 r2;

    rv3 = 1;
    if (p1 != 0) {
        rv3 = 0;
    } else {
        t0 = D_00482894;
        EvObjSubSetTargetCount_351fa0(D_004E7110, t0);
        r1 = ((s32)GetEventObjMgr_2d1960());
        t1 = D_0047F0C0;
        t2 = D_0047F0C4;
        r2 = EventObjMgrCreateM05Change_2e9f70(r1, t1, t2, D_004E7110);
        rv3 = 1;
    }
    return rv3;
}
