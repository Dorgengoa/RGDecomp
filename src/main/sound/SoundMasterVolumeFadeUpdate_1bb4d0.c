#include "types.h"

extern s32 D_004814B0[2];
extern f32 D_004814B8[2];
extern f32 D_004814C0[2];
extern f32 D_004814C8[2];

extern void SoundSendCmd_1b6cc0(s32, s32, s32, s32);

void SoundMasterVolumeFadeUpdate_1bb4d0(void)
{
    s32 i;
    f32 v;
    s32 v2;

    i = 0;
    do {
        if (D_004814B0[i] != 0) {
            f32 delta = D_004814C8[i];
            D_004814C0[i] += delta;
            if (delta > 0.0f) {
                if (D_004814C0[i] > D_004814B8[i]) {
                    D_004814C0[i] = D_004814B8[i];
                    D_004814B0[i] = 0;
                }
            } else {
                if (D_004814C0[i] < D_004814B8[i]) {
                    D_004814C0[i] = D_004814B8[i];
                    D_004814B0[i] = 0;
                }
            }
            v = D_004814C0[i];
            if (i >= 0 && i < 2) {
                if (v < 0.0f) {
                    v = 0.0f;
                }
                if (!(v <= 1.0f)) {
                    v = 1.0f;
                }
                v2 = (s32)(16383.0f * v);
                SoundSendCmd_1b6cc0(0xC, 2, v2, v2);
            }
        }
        i += 1;
    } while (i < 2);
}
