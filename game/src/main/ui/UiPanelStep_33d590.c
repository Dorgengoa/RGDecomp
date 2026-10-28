/* rgp:protos */
#define RGP_SELF_UiPanelStep_33d590 1
#define RGP_SELF_feq 1
#define RGP_SELF_feq0 1
#define RGP_SELF_recip 1
#define RGP_SELF_recip2 1
#define RGP_SELF_setp 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Sub {
    u8 pad[4];
    s16 f4;
} Sub;

typedef struct Node {
    u8 pad[0x20];
    Sub *f20;
} Node;

typedef struct Self {
    u8 pad[0x44];
    s32 f44;
    s32 f48;
    s32 f4C;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D94C;
extern f32 D_0047DAA0;
extern f32 D_0047DAB0;

static inline s32 feq0(f32 f) { return f == 0.0f; }
static inline s32 feq(f32 a, f32 b) { return a == b; }
static inline f32 recip(s32 n) { return 1.0f / (f32)n; }
static inline f32 recip2(s32 a, s32 b) { return 1.0f / (f32)(a * b); }
static inline void setp(s32 h, s32 n, f32 a, f32 b, f32 c) { UiFadeWidgetAlpha_290690(h, n, a, b, c); }
void UiPanelStep_33d590(Self *self) {
    s32 x;
    s32 y;
    s32 a;
    s32 b;
    s32 cc;
    s32 c8;
    s32 c4;
    s32 c0;
    s32 bc;
    s32 b8;
    s32 b4;
    s32 b0;
    s32 ac;
    s32 a8;
    s32 h;
    s32 w;
    s32 t;
    s32 i;
    s32 n;
    s32 base;
    s32 sub;
    s32 acc;
    s32 k;
    s32 d;
    Node *p;
    f32 f;

    h = ((s32)UiPanelGetWidgetList_33e860(self));
    w = GetDrawCtx_15de80();
    UiPanelGetOffset_33d530(self, &x, &y);
    t = DrawEnvGetHeight_1451d0(w);
    DrawEnvGetWidth_1451e0(w);
    UiPanelGetCellSize_33e920(self, &a, &b);
    n = t - b * (self->f4C + 2);
    UiSetWidgetPos_290f60(h, 1, x, (s32)((f32)n + (f32)(y)));
    if (((unsigned char)Bit64Test_33de60(self, 3)) != 0) {
        if (h == 0) {
            return;
        }
        if (w == 0) {
            return;
        }
        UiSetWidgetAlpha_2907a0(h, 1, 1.0f);
        UiPanelSetupFrameQuad_33e410(self);
        UiSetWidgetAlpha_2907a0(h, 2, 0.0f);
        UiFadeWidgetAlpha_290690(h, 2, 1.0f, D_0047DAB0, 0.0f);
        UiSetWidgetVisible_290010(h, 2, 1, 0);
        for (i = 0; i <= 32; i++) {
            n = i + 3;
            UiSetWidgetAlpha_2907a0(h, n, 0.0f);
            UiGetWidgetPos_2910a0(h, n, &cc, &c8);
            UiSetWidgetPos_290f60(h, n, 0, c8);
        }
        Bit64Assign_33de80(self, 3, 0);
        Bit64Assign_33de80(self, 4, 1);
        Bit64Assign_33de80(self, 8, 1);
        self->f44 = 0;
        UiPanelSetTimers_33e8f0(self, 10);
        return;
    }
    if (((unsigned char)Bit64Test_33de60(self, 8)) != 0) {
        CaptionPanelGetOffsetX_33df30(self);
        UiGetWidgetPos_2910a0(((s32)UiPanelGetWidgetList_33e860(self)), 2, &c4, &c0);
        UiSetWidgetPos_290f60(((s32)UiPanelGetWidgetList_33e860(self)), 2, 0, c0);
        if (UiPanelFrameWipeIn_33e320(self, 24.0f) != 0) {
            Bit64Assign_33de80(self, 8, 0);
        }
    }
    if (((unsigned char)Bit64Test_33de60(self, 9)) != 0) {
        UiPanelFrameWipeOut_33e220(self, 24.0f);
        DrawEnvGetWidth_1451e0(w);
        if (feq(UiGetWidgetAlpha_290770(((s32)UiPanelGetWidgetList_33e860(self)), 2), 0.0f)) {
            Bit64Assign_33de80(self, 9, 0);
            Bit64Assign_33de80(self, 10, 1);
        }
    }
    if (((unsigned char)Bit64Test_33de60(self, 4)) != 0) {
        base = CaptionPanelGetOffsetX_33df30(self);
        sub = UiPanelGetGlyphSpacing_33dfc0(self);
        UiPanelGetCellSize_33e920(self, &bc, &b8);
        acc = 0;
        for (i = 0; i < self->f44; i++) {
            n = i + 3;
            if (h == 0) {
                return;
            }
            p = ((Node *)UiFindWidget_290460(h, i + 2));
            if (i - 1 >= 0 && p != 0 && p->f20 != 0) {
                acc += p->f20->f4 - sub;
            }
            UiSetWidgetVisible_290010(h, n, 1, 0);
            UiFadeWidgetAlpha_290690(h, n, 1.0f, 0.0625f, -1.0f);
            UiGetWidgetPos_2910a0(h, n, &b4, &b0);
            UiMoveWidgetUniform_290f50(h, n, base + acc, b0, D_0047D94C, 0);
        }
        if (UiPanelStepTimer_33e870(self, 0) != 0) {
            return;
        }
        UiPanelSetTimers_33e8f0(self, 2);
        n = self->f44 + 3;
        self->f44++;
        if (((Node *)UiFindWidget_290460(h, n)) == 0) {
            Bit64Assign_33de80(self, 4, 0);
            Bit64Assign_33de80(self, 5, 1);
            UiPanelSetTimers_33e8f0(self, UiPanelGetWaitFrames_33d500(self));
        }
    }
    if (((unsigned char)Bit64Test_33de60(self, 5)) != 0) {
        if (UiPanelStepTimer_33e870(self, 0) != 0) {
            return;
        }
        d = self->f48;
        k = 32;
        if (d != 0) {
            k = 32 / d;
        }
        if (k <= 0) {
            k = 1;
        }
        UiPanelSetTimers_33e8f0(self, k);
        Bit64Assign_33de80(self, 5, 0);
        Bit64Assign_33de80(self, 6, 1);
        UiPanelGetTimer1_33e8b0(self);
        f = (f32)((self->f48 + 1) * UiPanelGetTimer1_33e8b0(self));
        UiFadeWidgetAlpha_290690(h, 2, 0.0f, 1.0f / f, -1.0f);
        self->f44 = 0;
    }
    if (((unsigned char)Bit64Test_33de60(self, 6)) != 0) {
        DrawEnvGetWidth_1451e0(w);
        for (i = 0; i < self->f44; i++) {
            n = i + 3;
            if (h == 0) {
                return;
            }
            UiGetWidgetPos_2910a0(h, n, &ac, &a8);
            UiFadeWidgetAlpha_290690(h, n, 0.0f, D_0047DAA0, -1.0f);
            UiMoveWidgetUniform_290f50(h, n, ac * 2, a8, 8.0f, 1);
        }
        if (UiPanelStepTimer_33e870(self, 0) != 0) {
            return;
        }
        Bit64Assign_33de80(self, 9, 1);
        UiPanelReloadTimers_33e8c0(self);
        n = self->f44 + 3;
        self->f44++;
        if (((Node *)UiFindWidget_290460(h, n)) == 0 || self->f44 >= self->f48 + 2) {
            Bit64Assign_33de80(self, 6, 0);
            Bit64Assign_33de80(self, 7, 1);
        }
    }
    if (((unsigned char)Bit64Test_33de60(self, 7)) != 0) {
        if (h == 0) {
            return;
        }
        f = UiGetWidgetAlpha_290770(h, self->f48 + 2);
        if (((unsigned char)Bit64Test_33de60(self, 10)) != 0 && f <= 0.0f) {
            UiPanelClose_33dc80(self);
        }
    }
    if (UiGetWidgetAlpha_290770(h, 1) <= 0.0f) {
        UiPanelClose_33dc80(self);
    }
}
