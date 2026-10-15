#include "types.h"

extern void SoundSendCmd_1b6cc0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
extern f32 D_0047E200;
extern s32 D_004814B0;

void SoundSetMasterVolume_1bb420(f32 fparg0) {
    f32 v;
    s32 t;

    v = fparg0;
    if (v < 0.0f) {
        v = 0.0f;
    }
    if (!(v <= 1.0f)) {
        v = 1.0f;
    }
    D_0047E200 = v;
    if (v < 0.0f) {
        v = 0.0f;
    }
    if (!(v <= 1.0f)) {
        v = 1.0f;
    }
    t = (s32)((f32)0x3FFF * v);
    SoundSendCmd_1b6cc0(0xC, 2, t, t, v);
    D_004814B0 = 0;
}
