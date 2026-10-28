/* rgp:protos */
#define RGP_SELF_MenuCatalogListPageScrollCb_35bba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Snd {
    u8 pad0[0x14];
    s32 x14;
} Snd;

typedef struct Gm {
    u8 pad0[0x1D0];
    f32 x1D0;
    u8 pad1D4[0x274 - 0x1D4];
    s32 x274;
    Snd *x278;
    u8 pad27C[8];
    s32 x284;
    s32 x288;
    s32 x28C;
} Gm;

typedef struct Menu {
    u8 pad0[0xA];
    s16 xA;
    u8 padC[2];
    s16 xE;
    u8 pad10[2];
    s16 x12;
    u8 pad14[2];
    s16 x16;
} Menu;

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
extern Gm *D_00482388;
extern u8 D_00482FEC;
extern s16 D_00482FF0;
extern u8 D_004B2570[];

#pragma optimization_level 3
#pragma opt_propagation off
s32 MenuCatalogListPageScrollCb_35bba0(Menu *a) {
    u8 *pad;
    s32 mode;
    s16 sel;

    MenuCatalogCursorUpdate_35eb10(D_00482388, 0);
    MenuCatalogRankPlayerRowPulse_360240(D_00482388);
    MenuCatalogTab1BlinkUpdate_35ddf0(D_00482388);
    MenuMobPreviewLoadPoll_35eee0(D_00482388);
    if (D_00482FEC != 0) {
        if (++D_00482FF0 > 2) {
            D_00482FEC = 0;
            D_00482FF0 = 0;
        }
    }
    pad = D_004B2570;
    SceneSoundGetSlot0HandleCur_207df0();
    if (D_00482FEC != 0) goto end;
    mode = D_00482388->x284;
    if (mode != 1 && mode != 2) goto end;
    if (PadIsTriggered_1839f0(pad, 0x8000)) {
        if (a->x12 > 0 || a->x16 > 0) MenuGridCursorRequestSe_28e9e0(D_00482388->x278, 0);
        if (a->x16 > 0) {
            a->x16 -= (s16)(a->xA + 1);
            if (a->x16 < 0) {
                a->x12 = 0;
                a->x16 = 0;
                MenuCatalogPlaceRowCursor_360350(D_00482388);
            }
            sel = a->x12;
            a->x12 = a->xA;
            MenuCatalogListRefresh_3602e0(D_00482388);
            a->x12 = sel;
        } else {
            a->x12 = 0;
            a->x16 = 0;
            MenuCatalogPlaceRowCursor_360350(D_00482388);
        }
        if (a->x16 < 0) a->x16 = 0;
        D_00482388->x288 = a->x12;
        D_00482388->x28C = a->x16;
        { f32 k = D_00482388->x1D0;
        UiMoveWidgetUniform_290f50(D_00482388->x274, 0x1F8, 0x173, (s32)(29.0f + (f32)a->x16 * k), 0.25f, 0);
        }
    } else if (PadIsTriggered_1839f0(pad, 0x2000)) {
        if (a->x12 < a->xA || a->x16 < a->xE - a->xA) MenuGridCursorRequestSe_28e9e0(D_00482388->x278, 0);
        if (a->x16 < a->xE - a->xA) {
            a->x16 += (s16)(a->xA + 1);
            if (a->x16 > a->xE - a->xA) {
                a->x12 = a->xA;
                a->x16 = a->xE - a->xA;
                MenuCatalogPlaceRowCursor_360350(D_00482388);
            }
            sel = a->x12;
            a->x12 = a->xA;
            MenuCatalogListRefresh_3602e0(D_00482388);
            a->x12 = sel;
        } else {
            a->x12 = a->xA;
            a->x16 = a->xE - a->xA;
            MenuCatalogPlaceRowCursor_360350(D_00482388);
        }
        if (a->x16 < 0) a->x16 = 0;
        D_00482388->x288 = a->x12;
        D_00482388->x28C = a->x16;
        { f32 k = D_00482388->x1D0;
        UiMoveWidgetUniform_290f50(D_00482388->x274, 0x1F8, 0x173, (s32)(29.0f + (f32)a->x16 * k), 0.25f, 0);
        }
    } else if ((D_00482388->x278->x14 & 1) && PadIsTriggered_1839f0(pad, 0x1000) && !PadIsRepeatTriggered_183dd0(pad, 0x1000)) {
        if (a->x12 == 0 && a->x16 == 0 && a->xE > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482388->x278, 0);
            a->x12 = a->xA;
            a->x16 = a->xE - a->xA;
            MenuCatalogPlaceRowCursor_360350(D_00482388);
            sel = a->x12;
            a->x12 = a->xA;
            MenuCatalogListRefresh_3602e0(D_00482388);
            a->x12 = sel;
            D_00482388->x288 = sel;
            D_00482388->x28C = a->x16;
            { f32 k = D_00482388->x1D0;
            UiSetWidgetPos_290f60(D_00482388->x274, 0x1F8, 0x173, (s32)(29.0f + (f32)a->x16 * k));
            }
        }
    } else if ((D_00482388->x278->x14 & 2) && PadIsTriggered_1839f0(pad, 0x4000) && !PadIsRepeatTriggered_183dd0(pad, 0x4000)) {
        if (a->x12 == a->xA && a->x16 == a->xE - a->xA && a->xE > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00482388->x278, 0);
            a->x12 = 0;
            a->x16 = 0;
            MenuCatalogPlaceRowCursor_360350(D_00482388);
            sel = a->x12;
            a->x12 = a->xA;
            MenuCatalogListRefresh_3602e0(D_00482388);
            a->x12 = sel;
            D_00482388->x288 = sel;
            D_00482388->x28C = a->x16;
            { f32 k = D_00482388->x1D0;
            UiSetWidgetPos_290f60(D_00482388->x274, 0x1F8, 0x173, (s32)(29.0f + (f32)a->x16 * k));
            }
        }
    }
end:
    return 1;
}
