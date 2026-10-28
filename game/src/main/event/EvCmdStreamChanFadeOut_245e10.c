/* rgp:protos */
#define RGP_SELF_EvCmdStreamChanFadeOut_245e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *gEventContext;

s32 EvCmdStreamChanFadeOut_245e10(s64 *arg0, s32 arg1) {
    s32 temp_20;
    s32 temp_19;
    s32 temp_18;
    s32 temp_17;
    f32 var_f0;

    temp_18 = *(s32 *)(gEventContext + 4) + 0x420;
    temp_20 = ScriptGetInt_2490f0((s32)arg0++);
    temp_19 = ScriptGetInt_2490f0((s32)arg0++);
    var_f0 = 0.0f;
    if (arg1 >= 3) {
        var_f0 = TaggedGetFloat_2490d0((s32)arg0);
    }
    EventVoiceSetChanVolumeFade_24e7d0(temp_18, temp_20, temp_19, var_f0);
    return 1;
}
