/* rgp:protos */
#define RGP_SELF_title_TitleLoadOpen_4eedc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EEDC0 -- build the LOAD-GAME panel's widget set and
 * drive its two-state fade-out.  Sibling of title_FUN_004EFEB0, which does the
 * same job for OPTIONS; the tail is the identical if/else-if chain on a gp s32
 * (`bnel $3,$0` carrying the NEXT GUARD'S constant, so a chain and not a
 * switch).
 *
 * The five-entry copy at 0x004EEF3C is a HAND-WRITTEN loop, not a struct
 * assignment: two moving cursors and a countdown, with the decrement scheduled
 * between the load and the store.
 *
 * D_0047FAA4 takes the address of a main-image function that splat did not
 * symbolise (the listing shows a bare `lui 0x37 / addiu`).  It has to be a
 * FUNCTION POINTER, not a literal cast: `(void *)0x373E10` compiles to
 * `lui / ORI` because the constant is unsigned, one bit different from
 * retail's `addiu`.  Taking a function's address gives %hi/%lo with a
 * relocation, which is `addiu`.
 */

extern f32 D_0047D518;
extern f32 D_0047D564;
extern f32 D_0047D56C;
extern f32 D_0047D570;
extern s16 D_00480400;
extern void (*D_0047FAA4)(void);
extern void *D_004841E0;
extern void *D_004841E4;
extern void *D_004841E8;
extern s32 D_004841EC;
extern s16 D_004841F0;
extern u8 title_D_004F1980;

/*rgp*/
extern void memset(void *p, s32 v, s32 n);
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

s32 title_TitleLoadOpen_4eedc0(void *unused, s32 first)
{
    s16 buf[5];
    s16 *src;
    s16 *dst;
    s32 n;

    if (first != 0) {
        title_TitleSceneOverlayModeOn_4eaa40();
        UiSetWidgetVisible_290010(D_004841E4, 1, 0, -1);
        memset((void *)&title_D_004F1980, 0, 0x70);
        title_TitleSaveSysInit_4ef2b0();
        title_TitleGetSaveCtx_4ef380();
        D_0047FAA4 = SaveSysResultCbMaybe_373e10;
        title_TitleLoadProgressWindowShow_4ede10(2, 0);
        D_004841F0 = 0;
        UiSetWidgetsVisibleById_291110(D_004841E4, 0xA, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004841E4, 0xA, 0.0f);
        UiFadeWidgetAlpha_290690(D_004841E4, 0xA, 1.0f, D_0047D564, -1.0f);
        UiSetWidgetPos_290f60(D_004841E4, 0xD, 5, 5);
        UiSetWidgetColor_2905b0(D_004841E4, 0xD, 0.0f, 0.0f, 0.0f, D_0047D56C);
        UiSetWidgetsVisibleById_291110(D_004841E4, 7, 1, 1);
        UiSetWidgetAlpha_2907a0(D_004841E4, 7, 0.0f);
        UiFadeWidgetAlpha_290690(D_004841E4, 7, 1.0f, D_0047D564, -1.0f);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x17, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x18, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x19, 1, 1);
        UiSetWidgetPos_290f60(D_004841E4, 0x19, 0x117, 0x1F);
        src = &D_00480400;
        dst = buf;
        n = 5;
        do {
            n = n - 1;
            *dst = *src;
            src = src + 1;
            dst = dst + 1;
        } while (n > 0);
        UiSetWidgetListVisibleById_28c190(D_004841E4, buf, 0);
        UiSetSpriteUv_28f970(D_004841E4, 0x14, 0xC0, 0x12, 0);
        UiSetWidgetPos_290f60(D_004841E4, 0x14, 0x30, 0xF);
        UiSetWidgetPos_290f60(D_004841E4, 0xF, -0x12, 0xC);
        UiSetWidgetPos_290f60(D_004841E4, 0xE, -0xF, 0xF);
        UiSetWidgetColor_2905b0(D_004841E4, 0xE, 0.0f, 0.0f, 0.0f, D_0047D56C);
        UiMoveWidgetUniform_290f50(D_004841E4, 0xF, 0x5A, 0xC, 0.25f, 0);
        UiMoveWidgetUniform_290f50(D_004841E4, 0xE, 0x5D, 0xF, 0.25f, 0);
        UiFadeWidgetAlpha_290690(D_004841E4, 0xF, 1.0f, D_0047D564, -1.0f);
        UiFadeWidgetAlpha_290690(D_004841E4, 0xE, D_0047D56C, D_0047D570, -1.0f);
        D_004841EC = 0;
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x10, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 8, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x1B, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x26, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x31, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x43, 0, 1);
        UiSetWidgetPos_290f60(D_004841E4, 8, 0xC8, 0);
        UiSetWidgetPos_290f60(D_004841E4, 0x1B, 0x38, 0x49);
        UiSetWidgetPos_290f60(D_004841E4, 0x26, 0x38, 0xC0);
        UiSetWidgetPos_290f60(D_004841E4, 0x31, 0x38, 0x137);
        UiSetWidgetPos_290f60(D_004841E4, 0x44, 0x1E5, 0x4A);
        UiSetWidgetPos_290f60(D_004841E4, 0x45, 0x1E9, 0x4C);
        title_TitleLoadPortSelectDraw_4ede70(-1);
        title_TitleLoadHighlightOption_4ede30(-1);
        title_TitleLoadSlotListRefreshMaybe_4edeb0(0);
        SaveUiScrollBarLayoutMaybe_377830(0x45, 0x15B, 3, 0x32, 0);
        title_TitleLoadFadeWidgets_4eda30(0);
        UiSetWidgetAlpha_2907a0(D_004841E4, 8, 0.0f);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x11, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004841E4, 0x12, 0, 1);
        title_TitleLoadShowMsg_4eeb60(-1);
        title_TitleSetNoAnalogPause_4f13b0(0);
    }
    SaveStepAndGetStatus_37bac0(0);
    if (D_004841EC == 0) {
        if (!(UiGetWidgetAlpha_290770(D_004841E4, 7) < 1.0f)) {
            D_004841EC = 1;
            UiFadeWidgetAlpha_290690(D_004841E4, 8, 1.0f, D_0047D564, -1.0f);
            UiMoveWidgetUniform_290f50(D_004841E4, 8, 0, 0, D_0047D518, 0);
            ScreenFadeIn_1cf740(GetCurrentScene_1f5be0(), 0xA);
        }
    } else if (D_004841EC == 1) {
        if (UiWidgetIsMoving_290d30(D_004841E4, 8) == 0) {
            UiEntryListResetRectByTag_28eb10(D_004841E8, 0x7532);
            StateMachineSetState_28ede0(D_004841E0, 8, 0);
        }
    }
    return 1;
}
