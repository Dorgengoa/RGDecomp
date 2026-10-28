/* rgp:protos */
#define RGP_SELF_MenuPartyGridSelectState_2a93d0 1
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

extern s32 D_0048235C;
extern s32 D_00482364;
extern u8 D_004B2570[];

s32 MenuPartyGridSelectState_2a93d0(void)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 rv5;
    s32 t2;
    s32 r2;
    s32 rv4;
    s32 t3;
    s32 r3;

    t0 = D_00482364;
    r0 = MenuGridCursorInput_28e170(t0, D_004B2570, 0, 0);
    t1 = D_00482364;
    r1 = UiEntryListGetCurrentData_28ec60(t1);
    rv5 = rv4;
    if (r0 == 1) {
        t2 = D_0048235C;
        r2 = StateMachineSetState_28ede0(t2, 0x49, 0);
        rv5 = r2;
    } else {
        rv4 = 2;
        if (r0 == 2) {
            t3 = D_0048235C;
            r3 = StateMachineSetState_28ede0(t3, 0x48, 0);
            rv4 = r3;
        }
        rv5 = rv4;
    }
    return 1;
}
