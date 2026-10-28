/* rgp:protos */
#line 1
#include "types.h"
#pragma divbyzerocheck on

extern "C" {
extern void VecScale_1cbca0(u8 *, u8 *, f32);
extern void VecSub_1cbd00(u8 *, u8 *, u8 *);
extern void VecAddXyzW1_1cbd80(u8 *, u8 *, u8 *);
extern void VecAddXyzW0_1cbda0(u8 *, u8 *, u8 *);
extern void VecWrapAngle_1cbe90(u8 *, u8 *);
extern u8 *EventPathRecGetPoint_2e4130(s32, s32);
extern s32 EventPathFindSegment_2e4420(s32, s32, s32 *);
extern s32 EventPathGetTotalLength_2e4550(s32);
extern s32 EventPathGetFlags_2e4560(s32);
extern s32 EventPathSegGetLength_2e4770(s32);
extern s32 EventPathSegGetToIdx_2e4780(s32);
extern s32 EventPathSegGetFromIdx_2e4790(s32);
extern s32 EventPathSegGetFlags_2e47a0(s32);
extern f32 EasingEval_2e4820(s32, f32);
}

extern "C" bool EventPathEvalXform_2e3da0(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 base;
    s32 key;
    u8 *a;
    u8 *b;
    bool ok;
    s32 len;
    f32 f;

    if (arg1 == 0) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg3 < 0) {
        arg3 = 0;
    }
    if (EventPathGetFlags_2e4560(arg2) & 0x80) {
        if (((short)EventPathGetTotalLength_2e4550(arg2)) > 0) {
            arg3 = arg3 % ((short)EventPathGetTotalLength_2e4550(arg2));
        } else {
            arg3 = 0;
        }
    }
    key = EventPathFindSegment_2e4420(arg2, arg3, &base);
    if (key == 0) {
        return 0;
    }
    a = EventPathRecGetPoint_2e4130(arg0, ((short)EventPathSegGetFromIdx_2e4790(key)));
    if (a == 0) {
        return 0;
    }
    b = EventPathRecGetPoint_2e4130(arg0, ((short)EventPathSegGetToIdx_2e4780(key)));
    if (b == 0) {
        return 0;
    }
    VecSub_1cbd00(arg1, b, a);
    VecSub_1cbd00(arg1 + 0x10, b + 0x10, a + 0x10);
    VecSub_1cbd00(arg1 + 0x20, b + 0x20, a + 0x20);
    if (((unsigned short)EventPathSegGetFlags_2e47a0(key)) & 0x80) {
        VecWrapAngle_1cbe90(arg1 + 0x10, arg1 + 0x10);
    }
    ok = true;
    arg3 -= base;
    len = ((short)EventPathSegGetLength_2e4770(key));
    if (arg3 < 0) {
        arg3 = 0;
        ok = false;
    }
    if (len < arg3) {
        arg3 = len;
        ok = false;
    }
    f = 0.0f;
    if (len >= 0) {
        f = (f32)arg3 / (f32)len;
        f = EasingEval_2e4820(((unsigned short)EventPathSegGetFlags_2e47a0(key)), f);
    } else {
        ok = false;
    }
    VecScale_1cbca0(arg1, arg1, f);
    VecScale_1cbca0(arg1 + 0x10, arg1 + 0x10, f);
    VecScale_1cbca0(arg1 + 0x20, arg1 + 0x20, f);
    VecAddXyzW0_1cbda0(arg1, arg1, a);
    VecAddXyzW0_1cbda0(arg1 + 0x10, arg1 + 0x10, a + 0x10);
    VecAddXyzW1_1cbd80(arg1 + 0x20, arg1 + 0x20, a + 0x20);
    if (arg4 != 0) {
        *(f32 *)(arg1 + 0x28) *= -1.0f;
        *(f32 *)(arg1 + 0x14) *= -1.0f;
    }
    return ok;
}
