/* rgp:protos */
#define RGP_SELF_EvScriptSoundSlotPlay_302600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptSoundSlotPlay_302600(s32 arg0, s32 arg1, s32 arg2)
{
    f32 var_f20;
    s32 var_19;

    if (arg2 > 0) goto A;
    return 1;
A:
    if (arg0 != -1) goto B;
    return 1;
B:
    if (arg2 >= 3) {
        var_19 = (ScriptArgGetInt_302d70(arg1 + 0xA) % 31) + 1;
    } else {
        var_19 = 0;
    }
    if (arg2 >= 2) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f20 = 1.0f;
    }
    SoundPlayScaledVolume_1b9520(arg0, ScriptArgGetInt_302d70(arg1), var_19, var_f20);
    return 1;
}
