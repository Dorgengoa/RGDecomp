#include "types.h"

extern void ScreenFadeIn_1cf740(s32, s32);
extern void ScreenFadeInColor_1cf750(s32, s32, f32, f32, f32);
extern void ScreenFadeReset_1cf760(s32);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 D_00481F78;

typedef struct { u8 b[8]; } E8_267ab0;

s32 EvCmdScreenFadeIn_267ab0(E8_267ab0 *arg0, s32 arg1) {
    s32 temp_16;
    s32 a;
    s32 b;
    s32 c;

    temp_16 = ScriptGetInt_26a2a0((s32) arg0++);
    switch (arg1) {
        case 1:
            ScreenFadeReset_1cf760(D_00481F78);
            ScreenFadeIn_1cf740(D_00481F78, temp_16);
            break;
        case 4:
            a = ScriptGetInt_26a2a0((s32) arg0++);
            b = ScriptGetInt_26a2a0((s32) arg0++);
            c = ScriptGetInt_26a2a0((s32) arg0);
            ScreenFadeReset_1cf760(D_00481F78);
            ScreenFadeInColor_1cf750(D_00481F78, temp_16, (f32) a, (f32) b, (f32) c);
            break;
    }
    return 1;
}
