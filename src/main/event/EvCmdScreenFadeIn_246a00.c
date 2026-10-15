#include "types.h"

s32 ScreenFadeIn_1cf740(s32, s32);
s32 ScreenFadeInColor_1cf750(s32, s32, f32, f32, f32);
s32 ScreenFadeReset_1cf760(s32);
s32 ScriptGetInt_2490f0(s32);
extern s32 D_0047E7E4;
extern s32 *gEventContext;

s32 EvCmdScreenFadeIn_246a00(s64 *arg0, s32 arg1)
{
    s32 id;
    s32 a;
    s32 b;
    s32 c;

    id = ScriptGetInt_2490f0((s32)arg0++);
    switch (arg1) {
    case 1:
        ScreenFadeReset_1cf760(*gEventContext);
        ScreenFadeIn_1cf740(*gEventContext, id);
        break;
    case 4:
        a = ScriptGetInt_2490f0((s32)arg0++);
        b = ScriptGetInt_2490f0((s32)arg0++);
        c = ScriptGetInt_2490f0((s32)arg0);
        ScreenFadeReset_1cf760(*gEventContext);
        ScreenFadeInColor_1cf750(*gEventContext, id, (f32)a, (f32)b, (f32)c);
        break;
    }
    D_0047E7E4 = 1;
    return 1;
}
