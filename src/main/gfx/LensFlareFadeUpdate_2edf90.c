#include "types.h"

extern s32 LensFlareIsEnabled_2ed820(void);
extern f32 D_0047D904;

typedef struct {
    u8 pad0[0x144];
    f32 unk144;
    s32 unk148;
} T2edf90_arg0;

void LensFlareFadeUpdate_2edf90(T2edf90_arg0 *arg0)
{
    f32 var_f0;
    s32 temp_4;

    if (LensFlareIsEnabled_2ed820() != 0) {
        temp_4 = arg0->unk148;
        switch (temp_4) {
        case 0:
            var_f0 = arg0->unk144 + D_0047D904;
            arg0->unk144 = var_f0;
            break;
        case 1:
            var_f0 = arg0->unk144 - D_0047D904;
            arg0->unk144 = var_f0;
            break;
        }
        if (arg0->unk144 < 0.0f) {
            arg0->unk144 = 0.0f;
        }
        if (!(arg0->unk144 <= 1.0f)) {
            arg0->unk144 = 1.0f;
        }
    }
}
