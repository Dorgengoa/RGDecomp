#include "types.h"

extern void UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern void MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern s32 UiEntryListGetCurrentData_28ec60(void *);
extern void InsectMenuPlacePromptSetDoneMaybe_3988b0(void);
extern void StateMachineSetState_28ede0(void *, s32, s32);

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
