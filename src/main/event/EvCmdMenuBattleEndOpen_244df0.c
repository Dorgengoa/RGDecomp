#include "types.h"

extern void FieldHudLogClose_203fa0(void);
extern void MenuBattleEndResLoad_2043b0(s32);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 GetStreamMgr_207ea0(void);
extern void StreamMgrPauseChan_1d6630(s32, s32);
extern void StreamMgrStopChan_1d66b0(s32, s32);
extern s32 StreamMgrStartChan_1d66f0(s32, s32, void *, s32);
extern s32 StreamMgrPlayChan_1d6670(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EA90[];
extern u8 D_0045EAA0[];
extern u8 D_0045EAB0[];

s32 EvCmdMenuBattleEndOpen_244df0(void)
{
    s32 r4;
    s32 r7;
    s32 r8;

    FieldHudLogClose_203fa0();
    MenuBattleEndResLoad_2043b0(1);
    TaskSetEnabled_27c2a0(1, D_0045EA90);
    TaskSetEnabled_27c2a0(1, D_0045EAA0);
    r4 = GetStreamMgr_207ea0();
    StreamMgrPauseChan_1d6630(r4, 0);
    StreamMgrStopChan_1d66b0(r4, 0);
    r7 = StreamMgrStartChan_1d66f0(r4, 0, D_0045EAB0, 0);
    r8 = StreamMgrPlayChan_1d6670(r4, 0, 1.0f);
    return 1;
}
