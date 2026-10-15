#include "types.h"

typedef struct S003452b0 {
    u8 pad0[0xC];
    s8 unkC;
    u8 padD[3];
    f32 v10[4];
    u8 pad20[0x20];
    f32 v40[4];
    f32 unk50;
    u8 pad54[0x90 - 0x54];
    f32 unk90;
    u8 pad94[0xA1 - 0x94];
    bool b0 : 1;
    bool b1 : 1;
    s16 unkA2;
} S003452b0;

extern "C" {
f32 VecDistance_13d3d0(void *arg0, void *arg1);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32 arg0, s32 arg1, s32 arg2, f32 arg3);
s32 SceneSoundGetSlot0HandleCur_207df0(void);
void sceVu0CopyVector(void *arg0);
}

extern "C" f32 HatenaMarkProximityCheck_3452b0(S003452b0 *arg0, s32 pd, s32 arg2)
{
    f32 f;

    sceVu0CopyVector(arg0->v40);
    f = VecDistance_13d3d0(arg0->v40, arg0->v10);
    if (f <= arg0->unk90) {
        arg0->unkA2 = arg2;
        if (arg2 == 0) {
            arg0->unkC = 1;
            if (arg0->b1) {
                SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 0x18, SoundNextPlayHandle_1b81c0(), 1.0f);
                arg0->b1 = 0;
            }
        } else {
            arg0->unkC = 3;
        }
    } else if (arg0->unkA2 < 0) {
        arg0->unkC = 0;
        arg0->unkA2 = -1;
        arg0->b1 = 1;
    }
    if (arg2 == 0) {
        arg0->unk50 = f;
    }
    return f;
}
