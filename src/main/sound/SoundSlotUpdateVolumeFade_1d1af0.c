#include "types.h"

typedef struct S001d1af0 {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0xC];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} S001d1af0;

extern void SoundSetCategoryVolume_1bb230(s32 arg0, f32 arg1);
extern s32 SoundSlotGetBankId_1d2130(S001d1af0 *arg0);
extern s32 SoundSlotGetIndex_1d2140(S001d1af0 *arg0);
extern s32 SoundSlotGetHandle_1d2150(S001d1af0 *arg0);
extern void SoundSlotSetSkipVolume_1d2180(S001d1af0 *arg0, s32 arg1);
extern s32 SoundSlotIsSkipVolume_1d21b0(S001d1af0 *arg0);
extern s32 SoundSlotHasFlag2Maybe_1d21c0(S001d1af0 *arg0);
extern s32 SoundSlotIsMuted_1d21d0(S001d1af0 *arg0);

void SoundSlotUpdateVolumeFade_1d1af0(S001d1af0 *arg0, f32 arg1)
{
    f32 d;
    f32 v;
    f32 t;

    if (SoundSlotGetBankId_1d2130(arg0) < 0) {
        return;
    }
    if (SoundSlotGetHandle_1d2150(arg0) == -1) {
        return;
    }
    d = arg0->unk28;
    if (d != 0.0f) {
        arg0->unk20 = arg0->unk20 + d;
        if (arg0->unk28 > 0.0f) {
            if (arg0->unk20 >= arg0->unk2C) {
                arg0->unk20 = arg0->unk2C;
                arg0->unk28 = 0.0f;
            }
        }
        if (arg0->unk28 < 0.0f) {
            if (arg0->unk20 <= arg0->unk2C) {
                arg0->unk20 = arg0->unk2C;
                arg0->unk28 = 0.0f;
            }
        }
    }
    if (SoundSlotGetIndex_1d2140(arg0) == 4) {
        SoundSlotSetSkipVolume_1d2180(arg0, 1);
    }
    if (SoundSlotHasFlag2Maybe_1d21c0(arg0) != 0) {
        SoundSlotSetSkipVolume_1d2180(arg0, 1);
    }
    if (SoundSlotIsSkipVolume_1d21b0(arg0) == 0 && arg0->unk10 >= 0) {
        if (SoundSlotIsMuted_1d21d0(arg0) != 0) {
            v = 0.0f;
        } else {
            v = arg0->unk20;
        }
        t = arg1 * v;
        if (t != arg0->unk24) {
            SoundSetCategoryVolume_1bb230(SoundSlotGetBankId_1d2130(arg0), t);
            arg0->unk24 = t;
        }
    }
    SoundSlotSetSkipVolume_1d2180(arg0, 0);
}
