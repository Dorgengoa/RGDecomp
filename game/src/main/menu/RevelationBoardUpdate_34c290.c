/* rgp:protos */
#define RGP_SELF_RevelationBoardUpdate_34c290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
extern f32 D_0047D400 __attribute__((section(".sdata")));
extern f32 D_0047D628;
extern f32 D_0047D634;
extern u8 D_004B2570[];

typedef struct { u8 b0; u8 lo : 1; u8 f : 4; u8 hi : 3; u8 b2; u8 b3; } Bf;

#define A0 (*(s32 *)(arg0 + 0))
#define A8 (*(s32 *)(arg0 + 8))
#define AC (*(s32 *)(arg0 + 0xC))
#define X76C (*(s16 *)(arg0 + 0x76C))
#define X76E (*(s16 *)(arg0 + 0x76E))
#define X770 (*(s16 *)(arg0 + 0x770))

void RevelationBoardUpdate_34c290(u8 *arg0) {
    u8 *g;
    s16 st;
    u8 *p;
    u8 *q;
    s32 i;
    u8 *tbl;
    u8 *e;
    s32 n;
    u8 *it;
    u16 *s;

    g = ((u8 *)GetGameData_1fede0());
    if (g == NULL) {
        return;
    }
    *(s32 *)(arg0 + 0x77C) = UiGetWidgetColor_2904b0(A0, 0x47);
    *(f32 *)(arg0 + 0x778) = 0.5f + Sinf_128fd0(D_0047D400 * (f32)*(s16 *)(arg0 + 0x18)) / 2.0f;
    *(s16 *)(arg0 + 0x18) = (*(s16 *)(arg0 + 0x18) + 1) % 120;
    if (X76E != 0) {
        UiFadeWidgetAlpha_290690(A0, 0x4F, 0.0f, D_0047D628, -1.0f);
        X770 = X770 + 1;
        st = X76E;
        if (st == 1) {
            if (RevelationBoardCursorZoomInMaybe_34ca30(arg0) != 0) {
                X76E = 2;
                X770 = 0;
            }
        } else if (st == 2) {
            if (X770 == 1) {
                SoundPlayScaledVolume_1b9520(A8, 0x25, 0, 1.0f);
            }
            if (X770 >= 5) {
                X76E = 3;
                X770 = 0;
            }
        } else if (st == 3) {
            if (RevelationBoardCommitAnimMaybe_34c7f0(arg0) != 0) {
                X76E = 4;
                X770 = 0;
            }
        } else if (st == 4) {
            UiSetWidgetsVisibleById_291110(A0, 0xB5, 0, 1);
            UiSetWidgetsVisibleById_291110(A0, 0x58, 0, 1);
            if (X76C == 2) {
                X76E = 5;
                X770 = 0;
                SoundPlayScaledVolume_1b9520(A8, 0x27, 0, 1.0f);
            } else {
                X76C = -1;
                X76E = 0;
                X770 = 0;
            }
        } else if (st == 5) {
            if (X770 >= 0x3C) {
                X76E = 6;
                X770 = 0;
                StreamPlayMwv_207340(0x325, 0, 1.0f);
            }
        } else if (st == 6) {
            X770 = X770 % 240;
        } else if (st == 7) {
            if (X770 != 1 && X770 >= 0x3C) {
                SoundPlayScaledVolume_1b9520(A8, 0x26, 0, 1.0f);
                X76E = 8;
                X770 = 0;
                RevelationBoardRefreshMaybe_3eaec0(g, AC, 0);
                p = ((u8 *)RevelationBoardGetCells_3eb510(g, AC, 0, 0));
                q = arg0 + 0x1C;
                for (i = 0; i < 0x1D4; i++) {
                    if (*q & 1) {
                        ((Bf *)p)->f = 14;
                    }
                    p += 4;
                    q += 4;
                }
            }
        } else if (st == 8) {
            if (X770 >= 0x3C) {
                X76C = -1;
                X76E = 0;
                X770 = 0;
                StreamSetChanVolumeFade_1cd960(((s32)GetLoaderMgr_1f59d0()), 0, 0xF, 1.0f);
            }
        } else {
            X76C = -1;
            X76E = 0;
            X770 = 0;
        }
        if (X76C == -1) {
            UiFadeWidgetAlpha_290690(A0, 0x4F, 1.0f, D_0047D634, -1.0f);
            RevelationBoardRefreshMaybe_3eaec0(g, AC, 0);
        }
    }
    if (IsTgsDemoBuild_207f20() != 0) {
        return;
    }
    if (ReturnZero_207fe0() == 0) {
        return;
    }
    if (PadIsHeld_183a20(D_004B2570, 2) == 0) {
        return;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x10) == 0) {
        return;
    }
    it = ((u8 *)RevelationBoardFindById_3eb580(g, AC, 0, 0));
    tbl = ((u8 *)RevelationBoardGetCells_3eb510(g, AC, 0, 0));
    if (it == NULL) {
        return;
    }
    if (tbl == NULL) {
        return;
    }
    e = ((u8 *)RevelationBoardCellGetEntry_3eae10(g, AC, tbl + (*(s16 *)(arg0 + 0x10) + *(s16 *)(arg0 + 0x12) * 26) * 4, (int)((*(short *)((char *)arg0 + 0x10)))));
    if (e == NULL) {
        return;
    }
    SoundPlayScaledVolume_1b9520(A8, 0xA, 0, 1.0f);
    n = *(s16 *)(e + 0xC);
    s = *(u16 **)(e + 0x10);
    i = 0;
    while (i < n) {
        s16 *r = *(s16 **)(*(u8 **)(it + 0x10) + (s16)s[1] * 4);
        if (r != NULL) {
            InvAddItemCoreMaybe_3c6540(*(s32 *)(g + 0x18), *r, 0xA, 1, -1, 0, 0);
        }
        i++;
        s += 2;
    }
    RevelationBoardRefreshMaybe_3eaec0(g, -1, 0);
}
