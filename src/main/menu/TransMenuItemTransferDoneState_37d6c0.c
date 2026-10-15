#include "types.h"

extern void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048470C;
extern s32 D_00484740;

s32 TransMenuItemTransferDoneState_37d6c0(void)
{
    s32 r1;

    MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
    r1 = StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
    return 1;
}
