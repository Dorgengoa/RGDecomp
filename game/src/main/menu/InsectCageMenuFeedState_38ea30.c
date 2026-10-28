/* rgp:protos */
#define RGP_SELF_InsectCageMenuFeedState_38ea30 1
#include "port/game_protos.h"
#line 1
#define KU 1
#define KI 1
#define KD 2
#define KA 6
#pragma optimization_level 3
#include "types.h"
#ifndef KA
#define KA 0
#endif

typedef struct { s32 m[12]; } M34;
typedef struct { u16 id; s8 b; s8 pad; } TE;
typedef struct { s16 x, y; } P2;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004E94FC[0x400];
extern s16 D_00483370;
extern s16 D_00483374;
extern u8 D_004E9510[];
extern s32 D_004832D8;
extern u8 D_004832A0[8];
extern u8 D_004E9520[0x400];
extern TE D_004542E0[];
extern s32 D_00483304;
extern u8 D_004E9528[0x400];
extern u8 D_00464110[];

s32 InsectCageMenuFeedState_38ea30(void *self, s32 arg1)
{
    s32 x2ac;
    s32 y2a8;
    s32 x;
    s32 y;
    s32 x29c;
    s32 y298;
    s32 x294;
    s32 y290;
    M34 v260 __attribute__((aligned(16)));
    M34 v230 __attribute__((aligned(16)));
    M34 m200 __attribute__((aligned(16)));
    s32 v1c0[16] __attribute__((aligned(16)));
    s32 v180[16] __attribute__((aligned(16)));
    u8 *ents[16];
    P2 *cs[16];
    P2 *bs[16];
    M34 m90 __attribute__((aligned(16)));
    s32 flags;
    u8 *w;
#if KU
    s32 a;
#else
    u8 a;
#endif
    u16 id;
    s32 b;
#if KT
    TE *te;
    s32 i;
#else
    s32 i;
    TE *te;
#endif
    u8 *e;
    s32 d;
    s32 k;

    flags = *(s32 *)D_004E94FC;
    w = ((u8 *)InsectCageMenuGetCursorObj_390f70());
    switch (D_00483370) {
    case 0:
        D_00483374 = 0;
        D_00483370 = D_00483370 + 1;
        break;
    case 1:
#if KA == 1
        if (*(s32 *)D_004E9528 <= 0) {
#elif KA == 2
        if (!(*(s32 *)D_004E9528 >= 1)) {
#elif KA == 3
        if (1 > *(s32 *)D_004E9528) {
#elif KA == 4
        if ((*(s32 *)D_004E9528 < 1) != 0) {
#elif KA == 5
        if ((u32)(*(s32 *)D_004E9528 < 1)) {
#elif KA == 6
        b = *(s32 *)D_004E9528 < 1;
        if (b) {
#else
        if (*(s32 *)D_004E9528 < 1) {
#endif
            ModelObjPlayMotionByName_1867a0(w, D_00464110, 0);
            SoundPlayScaledVolume_1b9520(GameSceneSoundSlot1GetHandle_1d07b0(GetCurrentScene_1f5be0()), 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
            MenuObjSetHideModels_385700(D_004832D8);
            D_00483370 = D_00483370 + 1;
        }
        break;
    case 2:
        if (++D_00483374 > 0x3C) {
#if KU
            a = MenuObjInsectIsFullyGrown_386c40(w, 0, 0, 0) & 0xFF;
#else
            a = (u8)MenuObjInsectIsFullyGrown_386c40(w, 0, 0, 0);
#endif
            b = MenuObjInsectIsAdult_386c90(w, 0, 0, 0) != 0;
            if (a != 0) {
                PlayMenuSe_289ef0(5);
            } else {
                InsectCageSePlay_3844b0(D_004832A0, 4);
            }
            InsectStatsGet_386a10(w, &v260, 0, 0);
            InsectApplyItem_3cf310(InsectCageMenuGetCurCageItem_391030(), *(s32 *)D_004E9520, *(s32 *)(w + 0x96C), 0);
            InsectStatsGet_386a10(w, &v230, 0, 0);
            InsectCageMenuRefreshPreview_3896a0(w);
            UiSetWidgetVisible_290010(arg1, 0x75D0, 1, -1);
            UiGetWidgetPos_2910a0(arg1, 0xC350, &x2ac, &y2a8);
            UiSetWidgetPos_290f60(arg1, 0xC350, x2ac, y2a8);
            UiSetWidgetVisible_290010(arg1, 0xC350, 1, -1);
            InsectStatsDiff_3841d0(&m90, &v230, &v260);
            {
                s32 *s_ = (s32 *)&m90;
                s32 *d_ = (s32 *)&m200;
                s32 n_ = 6;
                do {
                    n_--;
                    d_[0] = s_[0];
                    d_[1] = s_[1];
                    s_ += 2;
                    d_ += 2;
                } while (n_ > 0);
            }
            InsectStatsCompact_384290(&m200, v1c0);
            InsectStatsCompact_384290(&v230, v180);
            UiSetWidgetPos_290f60(arg1, 0x75C6, 0, 0);
#if KI
            for (i = 0; (id = (te = &D_004542E0[i])->id) != 0; i++) {
                ents[i] = ((u8 *)UiFindWidget_290460(arg1, id));
#else
            for (i = 0; (te = &D_004542E0[i])->id != 0; i++) {
                ents[i] = ((u8 *)UiFindWidget_290460(arg1, te->id));
#endif
                bs[i] = 0;
                if (ents[i] != 0) {
                    cs[i] = *(P2 **)(ents[i] + 0x20);
                    k = *(s32 *)(ents[i] + 0x24);
                    if (k != 0) bs[i] = (P2 *)(k + (te->b << 5));
                }
            }
            UiSetWidgetVisible_290010(arg1, 0x75C6, 1, -1);
            for (i = 0; i < 11; i++) {
                x = 0;
                te = &D_004542E0[i];
                y = 0;
                if (te->id == 0) break;
                UiGetWidgetAbsPos_290fc0(arg1, te->id, &x, &y);
                if (cs[i] != 0) {
                    x -= cs[i]->x;
                    y -= cs[i]->y;
                }
                if (bs[i] != 0) {
                    x += bs[i]->x;
                    y += bs[i]->y;
                }
#if KD
                {
                    s32 *pd_ = &v1c0[i];
                    d = *pd_;
                }
#else
                d = v1c0[i];
#endif
#if KD == 2
                if (v1c0[i] == 0) {
                    UiSetSubItemPos_28f200(arg1, 0x75C6, x, -30, i);
                    continue;
                }
#else
                if (d == 0) {
                    UiSetSubItemPos_28f200(arg1, 0x75C6, x, -30, i);
                    continue;
                }
#endif
                x -= 4;
                if (i < 4) y -= 4;
                if (te->id == 0xC36C) y += 6;
                if (a == 0) {
#if KD == 2
                    if (v1c0[i] > 0) {
                        UiSetSubItemGlyphUv_28f160(arg1, 0x75C6, 0, 0, i);
                    } else if (v1c0[i] < 0) {
#else
                    if (d > 0) {
                        UiSetSubItemGlyphUv_28f160(arg1, 0x75C6, 0, 0, i);
                    } else if (d < 0) {
#endif
                        UiSetSubItemGlyphUv_28f160(arg1, 0x75C6, 0, 0x20, i);
                    }
                }
                UiSetSubItemPos_28f200(arg1, 0x75C6, x, y, i);
                UiSetWidgetSubItemValue_291250(arg1, 0x75C6, i, (long long)(v180[i]));
            }
            UiSetWidgetPos_290f60(arg1, 0x75D0, x2ac - 2, y2a8 + 0x125);
            if (a != 0) {
                InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0x400, 0x4B2);
            } else if (MenuObjInsectIsFullyGrown_386c40(w, 0, 0, 0) != 0) {
                InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0x400, 0x4B3);
            } else if ((b & 0xFF) != MenuObjInsectIsAdult_386c90(w, 0, 0, 0)) {
                InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0x400, 0x4C4);
            } else {
                InsectCageMenuFormatMsgForCursor_388430(D_00483304 + 0x400, 0x4B1);
            }
            k = TextMeasureWidth_3910e0(D_00483304 + 0x400) + 0x1E;
            UiWindowFrameSetSize_388380(((s32)UiGetWidgetSprite_28fe10(arg1, 0x75D0, 0)), k + 2, 0x2A);
            UiGetWidgetPos_2910a0(arg1, 0xC350, &x29c, &y298);
            UiGetWidgetPos_2910a0(arg1, 0x75D0, &x294, &y290);
            x29c += (0x178 - k) / 2;
            UiSetWidgetPos_290f60(arg1, 0x75D0, x29c, y290);
            D_00483370 = D_00483370 + 1;
        }
        break;
    case 3:
        if (flags & 6) {
            PlayMenuSe_289ef0(5);
            InsectCageItemIconReset_386070(D_004E9510);
            MenuObjSetPlayStandMotion_3849e0(D_004832D8);
            UiSetWidgetVisible_290010(arg1, 0xC350, 0, -1);
            UiSetWidgetVisible_290010(arg1, 0x75C6, 0, -1);
            InsectCageMenuRefreshPreview_3896a0(0);
            UiSetWidgetVisible_290010(arg1, 0x75D0, 0, -1);
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
        }
        break;
    }
    return 1;
}
