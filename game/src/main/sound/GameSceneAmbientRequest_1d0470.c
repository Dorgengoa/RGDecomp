/* rgp:protos */
#define RGP_SELF_GameSceneAmbientRequest_1d0470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct {
    u8 pad0[0xB49C];
    s32 unkB49C;
    s32 unkB4A0;
    s32 unkB4A4;
    s8 unkB4A8;
} O1d0470;

s32 GameSceneAmbientRequest_1d0470(O1d0470 *arg0, s32 arg1) {
    s32 var_5;
    s32 var_2;

    if (arg1 < 0) {
        return 0;
    }
    if (arg1 == arg0->unkB4A4) {
        return 0;
    }
    if (arg1 == arg0->unkB4A0) {
        return 0;
    }
    if (arg1 == arg0->unkB49C) {
        arg0->unkB4A4 = arg1;
        return 0;
    }
    if (arg0->unkB4A8 != 2) {
        var_5 = 2;
    } else {
        var_5 = 3;
    }
    if (GameSceneSoundSlotRequestLoad_1d0b20(arg0, var_5, 0, arg1) == 0) {
        return 0;
    }
    var_2 = 1;
    arg0->unkB4A4 = arg1;
    return var_2;
}
