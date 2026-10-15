#include "types.h"

s32 ScreenFadeOutColor_1cf730(s32, s32, f32, f32, f32);
s32 ScreenFadeReset_1cf760(s32);
s32 ScriptGetInt_2490f0(s32);
extern s32 D_0047E7E4;
extern s32 *gEventContext;

s32 EvCmdScreenFadeOut_246900(s64 *arg0, s32 arg1) {
    s32 id;
    s32 x;
    s32 y;
    s32 z;

    id = ScriptGetInt_2490f0((s32)arg0++);
    switch (arg1) {
    case 1:
        ScreenFadeReset_1cf760(*gEventContext);
        ScreenFadeOutColor_1cf730(*gEventContext, id, 0.0f, 0.0f, 0.0f);
        break;
    case 4:
        x = ScriptGetInt_2490f0((s32)arg0++);
        y = ScriptGetInt_2490f0((s32)arg0++);
        z = ScriptGetInt_2490f0((s32)arg0++);
        ScreenFadeReset_1cf760(*gEventContext);
        ScreenFadeOutColor_1cf730(*gEventContext, id, (f32)x, (f32)y, (f32)z);
        break;
    }
    D_0047E7E4 = 0;
    return 1;
}
