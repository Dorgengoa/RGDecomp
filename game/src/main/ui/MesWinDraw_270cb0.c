/* rgp:protos */
#define RGP_SELF_Calc 1
#define RGP_SELF_MesWinDraw_270cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rect {
    s32 x, y, w, h;
} Rect;

typedef struct Self {
    u8 pad0[0x40];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    s16 f54;
    s16 f56;
    u8 pad58[0x48];
    s32 fA0;
    s32 fA4;
    u8 padA8[0x18A4];
    s32 f194C;
    u8 pad1950[0x4A0];
    s32 f1DF0;
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
extern s32 D_0045F200[];

static inline void Calc(Self *self, Rect *r) {
    s16 k;
    MesWinCalcPos_2710b0(self);
    k = D_0045F200[0] - 1;
    r->x = self->f40 - (k + 8);
    r->y = self->f44 - 13;
    r->w = (k << 1) + 16 + self->f54;
    r->h = self->f56 + 26;
}

void MesWinDraw_270cb0(Self *self) {
    Rect r __attribute__((aligned(16)));
    Rect r2 __attribute__((aligned(16)));
    s32 w;
    s32 t;
    s32 g;
    s32 v;
    f32 f80;

    if (self->f194C == -1) {
        return;
    }
    w = GetDrawCtx_15de80();
    if (w == 0) {
        return;
    }
    t = DrawEnvGetWidth_1451e0(w);
    DrawEnvGetHeight_1451d0(w);
    g = ((s32)DrawListBeginPrim_141b00(w));
    if (g == 0) {
        return;
    }
    r.x = 0;
    r.y = 0;
    r.w = self->f54;
    r.h = self->f56;
    MesWinApplyRectOverride_2713a0(self, &r);
    switch (((short)MesWinGetFrameType_272b20(self))) {
    case 0:
        Calc(self, &r);
        break;
    case 9:
        self->f54 = 400;
        self->f56 = 80;
    case 1:
        Calc(self, &r);
        GsPktSetScissorRows_26ff00(g, self->f50, self->f52);
        r2.x = r.x - 48;
        r2.y = r.y;
        r2.w = r.w + 96;
        r2.h = r.h - 6;
        RectScaleCentered_26f9b0(&r2, 0.5f + 0.5f * MesWinGetOpenRate_277540(self));
        f80 = 80.0f;
        r2.y = r.y;
        r2.h = r.h - 6;
        MesWinDrawFrameBg_277720(g, &r2, 0, 0, 0, (s32)f80);
        GsPktSetScissorFull_26fe60(g);
        break;
    default:
        self->f40 = 0;
        self->f44 = 0;
        break;
    }
    if (((short)MesWinGetFrameType_272b20(self)) == 1 && MesWinGetOpenRate_277540(self) < 1.0f) {
        DrawListEndPrim_141a20(w);
        MesWinSetPageFrames_271ed0(self, 0);
        return;
    }
    if (self->fA0 >= 0) {
        self->f40 = self->fA0;
    } else {
        self->f40 = r.x;
    }
    if (self->fA4 >= 0) {
        self->f44 = self->fA4;
    } else {
        self->f44 = r.y;
    }
    if (((short)MesWinGetFrameType_272b20(self)) == 1 || ((short)MesWinGetFrameType_272b20(self)) == 9) {
        MesWinCalcPos_2710b0(self);
    } else if (((short)MesWinGetFrameType_272b20(self)) == 0) {
        self->f40 = LerpOffsetMaybe_2726a0(0.0f, (f32)t, (f32)MesWinGetPageMaxLineWidth_273a80(self, ((short)MesWinGetPage_272230(self))), 0.5f);
    }
    MesWinDrawGlyphs_271b70(self, g);
    if (((signed char)MesWinGetSeEnabled_272b40(self)) != 0 && MesWinGetPageFrames_271ec0(self) == 4) {
        ScenePlaySe_277690(self->f1DF0);
    }
    GsPktSetup2DState_26fdc0(g);
    MesWinUpdateArrowPos_2718c0(self);
    MesWinDrawChoiceArrow_271730(self, g);
    MesWinDrawPageIcon_2713f0(self, g);
    DrawListEndPrim_141a20(w);
    MesWinDrawName_271220(self);
}
