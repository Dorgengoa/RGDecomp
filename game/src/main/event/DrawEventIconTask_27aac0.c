/* rgp:protos */
#define RGP_SELF_DrawEventIconTask_27aac0 1
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

extern s32 D_0047E9AC;

s32 DrawEventIconTask_27aac0(void)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv3;
    s32 rv4;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 t3;
    s32 r5;

    r0 = GetCurrentScene_1f5be0();
    t0 = D_0047E9AC;
    if (t0 != 0) {
        r1 = GetPauseStep_2f6660();
        rv3 = r1;
        if (r1 == 0) {
            t1 = D_0047E9AC;
            r2 = (EventIconUpdate_2789b0(t1), (s32)0);
            t2 = D_0047E9AC;
            rv3 = r2;
            rv4 = t2;
        } else {
            t3 = D_0047E9AC;
            rv3 = r1;
            rv4 = t3;
        }
        r5 = (EventIconDrawAll_278790(rv4), (s32)0);
        return r5;
    }
    return r0;
}
