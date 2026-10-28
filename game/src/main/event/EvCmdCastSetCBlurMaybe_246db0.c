/* rgp:protos */
#define RGP_SELF_EvCmdCastSetCBlurMaybe_246db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdCastSetCBlurMaybe_246db0(s64 *arg0, s32 arg1)
{
    f32 var_f0;
    s32 temp_17_2;
    s32 temp_17;
    s32 temp_16;
    s32 temp_16_2;

    temp_16 = *(s32 *)((u8 *)gEventContext + 4) + 0x60;
    temp_17 = EventCastFindKeyByName_24bb50(temp_16, ScriptGetCodeAddr_249050((s32)arg0++));
    temp_17_2 = ScriptGetInt_2490f0((s32)arg0++);
    temp_16_2 = EventCastGetObjId_24c160(temp_16, temp_17, 0);
    if (arg1 == 3) {
        var_f0 = TaggedGetFloat_2490d0((s32)arg0);
    } else {
        var_f0 = 1.0f;
    }
    GameSceneObjSetCBlurMaybe_1cf900(*(s32 *)((u8 *)gEventContext + 0), temp_16_2, var_f0, temp_17_2);
    return 1;
}
