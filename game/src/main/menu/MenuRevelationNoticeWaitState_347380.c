/* rgp:protos */
#define RGP_SELF_MenuRevelationNoticeWaitState_347380 1
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

s32 MenuRevelationNoticeWaitState_347380(void)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 t2;

    t0 = D_00482364;
    r0 = MenuGridCursorInput_28e170(t0, D_004B2570, 0, 0);
    t1 = D_00482364;
    UiEntryListGetCurrentData_28ec60(t1);
    if ((u32)(r0 + -1) < 2) {
        t2 = D_0048235C;
        StateMachineSetState_28ede0(t2, 0x78, 0);
    }
    return 1;
}
