#pragma opt_propagation off
#include "types.h"


extern void SoundStreamSlotGetBufInfo_1bd100(s16 arg0, s32 *arg1);
extern void SoundStreamSlotSetFillThreshold_1bd450(s16 arg0, f32 arg1);

typedef struct {
    u8 pad0[0x80];
    s16 unk80;
    u8 pad82[0x26];
    s32 unkA8;
} T1d6b10_arg0;

void StreamChanSetFillThreshold_1d6b10(T1d6b10_arg0 *arg0, f32 fparg0)
{
        s32 arg_h1;

    s32 sp30[4];
    f32 var_f20;
    s16 temp_4;

    temp_4 = arg0->unk80;
    var_f20 = fparg0;
    if (temp_4 >= 0) {
        if (var_f20 < 0.0f) {
            var_f20 = 0.0f;
        }
        if (!(var_f20 <= 1.0f)) {
            var_f20 = 1.0f;
        }
        SoundStreamSlotGetBufInfo_1bd100(temp_4, sp30);
        SoundStreamSlotSetFillThreshold_1bd450(arg0->unk80, var_f20);
        arg0->unkA8 = (s32)(var_f20 * (f32)sp30[0]);
    }
}
