/* rgp:protos */
#define RGP_SELF_InsectMenuPlacePromptWaitMaybe_397630 1
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

extern s32 D_004834F0;
extern u8 D_00483528;
extern u8 D_004B2570[];
extern u8 D_004E95E0[];

s32 InsectMenuPlacePromptWaitMaybe_397630(s32 p0, s32 p1)
{
    s32 r2;
    u8 t0;

    if (p1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E95E0, 0x7531, 0);
    }
    MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 1, 0);
    r2 = UiEntryListGetCurrentData_28ec60(D_004E95E0);
    t0 = D_00483528;
    if (t0 != 0) {
        InsectMenuPlacePromptSetDoneMaybe_3988b0();
        StateMachineSetState_28ede0(&D_004834F0, 0x7534, 0);
    }
    return 1;
}
