/* rgp:protos */
#define RGP_SELF_EvCmdSoundVolumeFade_244f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 *gEventContext;

s32 EvCmdSoundVolumeFade_244f40(s32 arg0, s32 arg1)
{
    s32 var_16;

    if ((arg1 != 1) && (arg1 != 2)) {
        return 0;
    }
    if (arg1 > 1) {
        var_16 = ScriptGetInt_2490f0(arg0 + 8);
    } else {
        var_16 = 0;
    }
    GameSceneSoundFadeVolume_1d0370(*gEventContext, var_16, TaggedGetFloat_2490d0(arg0));
    GameSceneSoundSlot4FadeTo_1d0610(*gEventContext, var_16, TaggedGetFloat_2490d0(arg0));
    return 1;
}
