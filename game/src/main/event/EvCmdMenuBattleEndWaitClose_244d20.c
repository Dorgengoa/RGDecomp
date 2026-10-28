/* rgp:protos */
#define RGP_SELF_EvCmdMenuBattleEndWaitClose_244d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045EA90[];
extern u8 D_0045EAA0[];

s32 EvCmdMenuBattleEndWaitClose_244d20(s32 arg0, s32 arg1) {
    s32 temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (((unsigned char)MenuBattleEndResIsRequested_2043e0()) == 0) {
        ScriptSetRefInt_249030(arg0, 0);
    } else if (MenuBattleEndOpenIfReady_204360() == 0) {
        ScriptSetRefInt_249030(arg0, 1);
        return 1;
    } else {
        temp_16 = ((unsigned char)MenuBattleEndIsOpen_204330()) & 0xFF;
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
