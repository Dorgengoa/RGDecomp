#include "types.h"

extern void FieldHudLogClose_203fa0(void);
extern void MenuBattleEndResLoad_2043b0(s32);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern void StreamPlayMwv_207340(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045F0C0[];
extern u8 D_0045F0D0[];

s32 EvCmdMenuBattleEndOpen_260180(void)
{
    FieldHudLogClose_203fa0();
    MenuBattleEndResLoad_2043b0(1);
    TaskSetEnabled_27c2a0(1, D_0045F0C0);
    TaskSetEnabled_27c2a0(1, D_0045F0D0);
    StreamPlayMwv_207340(0x320, 0, 1.0f);
    return 1;
}
