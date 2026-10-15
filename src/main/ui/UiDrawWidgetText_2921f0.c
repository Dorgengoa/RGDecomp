#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    void *unk4;
    u16 unk8;
} Spr002921F0;

typedef struct {
    u8 pad0[0xC];
    f32 unkC;
} Col002921F0;

s32 FontDrawText_26cdc0(void *, void *, s32, s32);
s32 FontWrapTextShrink_26d430(void *, void *, void *, s32, s32, u8 *);
s32 TextStyleSetAlpha_26dd40(void *, s32);
s32 FontGetLineAdvance_26f390(void *, s32 *);
s32 TextStyleSetSpaceWidth_26f5e0(void *, u8);
extern u8 D_004DB150[0x400];

void UiDrawWidgetText_2921f0(s32 arg0, s32 arg1, Spr002921F0 *arg2, s32 arg3, s32 arg4, Col002921F0 *arg5) {
    u8 flag;
    s32 sz;
    s32 buf[0x102];
    void *data;
    s32 hi;
    s32 lo;
    u16 v;
    s32 x;
    s32 y;

    data = arg2->unk4;
    if (data != NULL) {
        TextStyleSetAlpha_26dd40(D_004DB150, (s32)(128.0f * arg5->unkC));
        v = arg2->unk8;
        x = arg3 + arg2->unk0;
        y = arg4 + arg2->unk2;
        hi = v >> 7;
        lo = v & 0x7F;
        flag = 7;
        if (hi > 0 || lo > 0) {
            FontGetLineAdvance_26f390(D_004DB150, &sz);
            FontWrapTextShrink_26d430(D_004DB150, data, buf, hi, lo * sz, &flag);
            data = buf;
        }
        TextStyleSetSpaceWidth_26f5e0(D_004DB150, flag);
        FontDrawText_26cdc0(D_004DB150, data, x, y);
    }
}
