#include "types.h"

extern void MenuBattleEndResRelease_204250(void);
extern s32 MenuBattleEndIsOpen_204330(void);
extern s32 MenuBattleEndOpenIfReady_204360(void);
extern s32 ScriptSetRefInt_26a1e0(s32 arg0, s32 arg1);
extern void TaskSetEnabled_27c2a0(s32 zero, void *name);

extern u8 D_0045F0C0[];
extern u8 D_0045F0D0[];

/* The inner `if (temp_16 == 0)` guard is a branch-LIKELY in retail with the
   shared `return 1` constant duplicated into its annulled slot. mwcc threads
   the shared return block into a guard only once that block ALREADY has a
   threaded predecessor ahead of it -- the outer arm supplies one only when it
   is written as an early `return 1;` instead of as an `else`.
   [[levers.d/mwcc-branch-likely-duplication]] fix 3, reached from the if/else
   side. Inverting the INNER guard as well (`if (temp_16 != 0) return 1;`) is
   +2 words: only the OUTER arm becomes the early return. */
s32 EvCmdMenuBattleEndWaitClose_2600d0(s32 arg0, s32 arg1) {
    s32 temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (MenuBattleEndOpenIfReady_204360() == 0) {
        ScriptSetRefInt_26a1e0(arg0, 1);
        return 1;
    }
    temp_16 = MenuBattleEndIsOpen_204330() & 0xFF;
    ScriptSetRefInt_26a1e0(arg0, temp_16);
    if (temp_16 == 0) {
        MenuBattleEndResRelease_204250();
        TaskSetEnabled_27c2a0(0, D_0045F0C0);
        TaskSetEnabled_27c2a0(0, D_0045F0D0);
    }
    return 1;
}
