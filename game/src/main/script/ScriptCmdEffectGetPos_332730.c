/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetPos_332730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_004826E0;

s32 ScriptCmdEffectGetPos_332730(s32 arg0, s32 arg1) {
    u8 sp20[16] __attribute__((aligned(16)));
    s32 flag;

    if (arg1 != 4 && arg1 != 3) {
        return 0;
    }
    flag = 0;
    switch (arg1) {
    case 3:
    case 4:
        flag = D_004826E0;
    }
    if (flag == 0) {
        return 0;
    }
    EffectInstanceGetPos_2dd540(flag, sp20);
    ScriptSlotStoreVec3_334790(arg0, sp20);
    return 1;
    return 0;
}
