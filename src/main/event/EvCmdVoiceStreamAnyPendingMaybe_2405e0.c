#include "types.h"

extern s32 StreamGetChanStatus_1cd930(s32 arg0, s32 arg1);
extern s32 GetLoaderMgr_1f59d0(void);
extern void ScriptSetRefInt_249030(s32 arg0, s32 arg1);

extern f32 D_0047E8B8;
extern f32 D_0047E8BC;

s32 EvCmdVoiceStreamAnyPendingMaybe_2405e0(s32 arg0) {
    f32 sp58[2];
    s32 temp_18;
    s32 temp_2;
    s32 var_17;
    s32 var_16;

    temp_18 = GetLoaderMgr_1f59d0();
    var_17 = 0;
    var_16 = 0;
    sp58[0] = D_0047E8B8;
    sp58[1] = D_0047E8BC;
    while (var_16 < 2) {
        temp_2 = StreamGetChanStatus_1cd930(temp_18, *(s32 *)&sp58[var_16]);
        if (temp_2 == -1 || temp_2 == 3) {
            var_17 = 1;
            break;
        }
        var_16 += 1;
    }
    ScriptSetRefInt_249030(arg0, var_17);
    return 1;
}
