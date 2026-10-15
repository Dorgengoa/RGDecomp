#include "types.h"

extern void MenuBattleEndResRelease_204250(void);
extern s32 MenuBattleEndIsOpen_204330(void);
extern s32 MenuBattleEndOpenIfReady_204360(void);
extern s32 MenuBattleEndResIsRequested_2043e0(void);
extern void ScriptSetRefInt_249030(s32, s32);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern u8 D_0045EA90[];
extern u8 D_0045EAA0[];

s32 EvCmdMenuBattleEndWaitClose_244d20(s32 arg0, s32 arg1) {
    s32 temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (MenuBattleEndResIsRequested_2043e0() == 0) {
        ScriptSetRefInt_249030(arg0, 0);
    } else if (MenuBattleEndOpenIfReady_204360() == 0) {
        ScriptSetRefInt_249030(arg0, 1);
        return 1;
    } else {
        temp_16 = MenuBattleEndIsOpen_204330() & 0xFF;
        ScriptSetRefInt_249030(arg0, temp_16);
        if (temp_16 == 0) {
            MenuBattleEndResRelease_204250();
            TaskSetEnabled_27c2a0(0, D_0045EA90);
            TaskSetEnabled_27c2a0(0, D_0045EAA0);
        } else {
            return 1;
        }
    }
    return 1;
}
