#include "types.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef union {
    f32 f[4];
    u128 q;
} Vec;

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

struct CamBase {
    u8 d[0xC0];
};

class Cam : public CamBase {
public:
    V16(a) V16(b) V16(c)
    virtual void SetFov(f32);
};

extern "C" {
extern s32 Rand_133710(void);
extern void ModelSetScale_150ff0(u8 *, Vec *);
extern void ModelSetRot_151080(u8 *, Vec *);
extern void CameraSetLag_177170(u8 *, f32, f32);
extern void PadClearRepeatAll_183960(u8 *);
extern void PadSetRepeat_183d50(u8 *, s32, s32, s32);
extern void ModelObjPlayMotionByName_1867a0(u8 *, u8 *, s32);
extern u8 *GetWorldDataMgr_1fedf0(void);
extern void UiSlideInWidgetPair_28d010(s32, s32, s32);
extern void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern u8 *UiFindWidget_290460(s32, s32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void MenuCursorBobUpdate_35b1b0(u8 *, s32);
extern void MenuModelPageSetupMaybe_35b350(u8 *);
extern s32 WorldDataMgrNoRequestPending_3eef10(u8 *);
extern u8 D_00462BE8[];
extern u8 D_004B2570[];
extern f32 D_0047D35C;
extern f32 D_0047D470;
extern f32 D_0047D5B8;
extern f32 D_0047D5EC;
extern f32 D_0047D610;
extern f32 D_0047D624;
extern f32 D_0047F7E0;
extern f32 D_0047F7E4;
extern f32 D_0047F7F0;
extern f32 D_0047F7F4;
extern f32 D_0047F7F8;
extern f32 D_0047F7FC;
extern f32 D_0047F800;
extern f32 D_0047F804;
extern f32 D_0047F808;
extern f32 D_0047F80C;
extern u8 *D_00482380;
extern u8 D_004823CC;
extern u8 *D_004823D0;
extern u8 *D_004823D4;
extern s32 D_00482F68;
extern s32 D_00482F6C;
extern f32 D_00482F70;
extern s32 D_00482F7C;
extern s32 D_00482F80;
extern u8 D_00482F84;
extern u8 D_00482F90;
extern u8 D_00482F94;
}

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
#define G134 (*(s32 *)(D_00482380 + 0x134))

#define SETV(v, x, y, z) { BZERO(v, 16); (v)->f[0] = (x); (v)->f[1] = (y); (v)->f[2] = (z); }
static inline Vec *setv(Vec *v, f32 x, f32 y, f32 z) {
    BZERO(v, 16);
    v->f[0] = x;
    v->f[1] = y;
    v->f[2] = z;
    return v;
}

extern "C" s32 MenuModelPageOpenState_358840(s32 a0, s32 init) {
    Vec a;
    Vec b;
    Vec c;
    Vec d;
    Vec e;
    u8 *w;
    f32 f;

    if (init) {
        D_00482F68 = -1;
        D_00482F6C = -1;
        D_00482F90 = 0;
        D_00482F94 = 0;
        PadClearRepeatAll_183960(D_004B2570);
        PadSetRepeat_183d50(D_004B2570, 0xF000, 10, 3);
        PadSetRepeat_183d50(D_004B2570, 3, 10, 7);
    }
    switch (D_00482F68) {
    case -1:
        if (WorldDataMgrNoRequestPending_3eef10(GetWorldDataMgr_1fedf0()) == 0) {
            break;
        }
        w = UiFindWidget_290460(G134, 0x1D4);
        if (w == 0) {
            return 0;
        }
        if (*(s32 *)(w + 0x20) == 0) {
            return 0;
        }
        UiLayoutPanelFrame_28d580(*(s32 *)(w + 0x20), 0, 0, 0x174, 0x120, 0);
        UiSetWidgetVisible_290010(G134, 0x1D2, 0, -1);
        UiSetWidgetPos_290f60(G134, 0x1D2, 0x70, 0x47);
        UiSlideInWidgetPair_28d010(0x1B, 0x12, G134);
        UiFadeWidgetAlpha_290690(G134, 0x41, 1.0f, D_0047D610, -1.0f);
        MenuModelPageSetupMaybe_35b350(D_00482380);
        UiSetWidgetVisible_290010(G134, 0x1DD, 0, -1);
        UiSetWidgetAlpha_2907a0(G134, 0x1DE, 0.0f);
        MenuCursorBobUpdate_35b1b0(D_00482380, 1);
        if (D_004823D4 != 0) {
            { f32 *p_a = (f32 *)&a; p_a[0] = D_0047F7F0; p_a[1] = D_0047F7F4; p_a[2] = D_0047F7F8; p_a[3] = D_0047F7FC; }
            { f32 *p_b = (f32 *)&b; p_b[0] = D_0047F800; p_b[1] = D_0047F804; p_b[2] = D_0047F808; p_b[3] = D_0047F80C; }
            *(u128 *)(D_004823D4 + 0xE0) = a.q;
            *(u128 *)(D_004823D4 + 0xF0) = b.q;
            CameraSetLag_177170(D_004823D4, 1.0f, -1.0f);
            ((Cam *)D_004823D4)->SetFov(-1.0f);
        }
        if (D_004823D0 != 0) {
            D_004823CC = 1;
            ModelObjPlayMotionByName_1867a0(D_004823D0, D_00462BE8, 0);
            {
                u8 *g1 = D_004823D0;
                SETV(&c, 0.0f, D_0047D624, 0.0f);
                ModelSetRot_151080(g1, &c);
            }
            {
                u8 *g2 = D_004823D0;
                SETV(&d, D_0047D5B8, D_0047D5B8, D_0047D5B8);
                ModelSetScale_150ff0(g2, &d);
            }
            *(f32 *)(D_004823D0 + 0x170) = D_0047D5B8;
        }
        D_00482F68 = 0;
        D_00482F6C = 0;
        D_00482F70 = 0.0f;
        D_0047F7E0 = D_0047D5B8;
        D_0047F7E4 = D_0047D5B8;
        D_00482F7C = Rand_133710() % 5 + 3;
        D_00482F80 = 0;
        D_00482F84 = 0;
        D_00482F90 = 0;
        D_00482F94 = 0;
        break;
    case 0:
        f = D_00482F70 + D_0047D5EC;
        D_00482F70 = f;
        if (!(f < D_0047D35C)) {
            D_00482F70 = D_0047D35C;
            D_00482F68 = 1;
        }
        break;
    case 1:
        f = D_00482F70 - D_0047D5EC;
        D_00482F70 = f;
        if (f <= 1.0f) {
            D_00482F90 = 1;
            D_00482F70 = 1.0f;
            D_00482F68 = -2;
        }
        break;
    }
    switch (D_00482F6C) {
    case 0:
        { f32 x0 = *(volatile f32 *)&D_0047F7E0; D_0047F7E0 = x0 + D_0047D610; }
        D_0047F7E4 = D_0047F7E4 + D_0047D610;
        if (!(D_0047F7E0 <= 1.0f)) {
            D_0047F7E0 = 1.0f;
        }
        if (!(D_0047F7E4 <= 1.0f)) {
            D_0047F7E4 = 1.0f;
        }
        {
            f32 x3 = D_0047F7E0;
            u8 *g3 = D_004823D0;
            ModelSetScale_150ff0(g3, setv(&e, x3, x3, x3));
        }
        *(f32 *)(D_004823D0 + 0x170) = D_0047F7E4;
        if (!(D_0047F7E0 < 1.0f) && !(D_0047F7E4 < 1.0f)) {
            D_00482F6C = 1;
        }
        break;
    case 1:
        UiSetWidgetVisible_290010(G134, 0x1D2, 0, -1);
        UiSetWidgetVisible_290010(G134, 0x246, 1, -1);
        UiFadeWidgetAlpha_290690(G134, 0x246, 1.0f, 0.0625f, 0.0f);
        D_00482F6C = 2;
        break;
    case 2:
        if (!(UiGetWidgetAlpha_290770(G134, 0x246) <= D_0047D470)) {
            D_00482F94 = 1;
            D_00482F6C = -1;
        }
        break;
    }
    if (D_00482F90 == 0) {
        UiSetWidgetColor_2905b0(G134, 0x41, D_00482F70, D_00482F70, D_00482F70, 1.0f);
    }
    if (D_00482F90 != 0 && D_00482F94 != 0) {
        StateMachineSetState_28ede0(*(s32 *)(D_00482380 + 0x13C), 0x90, 0);
    }
    return 1;
}
