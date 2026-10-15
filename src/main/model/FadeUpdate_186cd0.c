#include "types.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x10];
    s32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} T186cd0_arg0;

void FadeUpdate_186cd0(T186cd0_arg0 *arg0, f32 arg1) {
    f32 f1;
    s32 z;

    if (arg0->unk14 == 0) {
        return;
    }
    z = arg0->unk0 == 0;
    if (arg0->unk18 < 0.0f) {
        if (z) {
            arg0->unk18 = 1.0f;
        } else {
            arg0->unk18 = 0.0f;
        }
    }
    if (z) {
        f1 = arg0->unk18 + arg0->unk1C * arg1;
        arg0->unk18 = f1;
        if (f1 > 1.0f) {
            arg0->unk18 = 1.0f;
        }
    } else {
        f1 = arg0->unk18 - arg0->unk20 * arg1;
        arg0->unk18 = f1;
        if (f1 <= 0.0f) {
            arg0->unk18 = 0.0f;
        }
    }
}
