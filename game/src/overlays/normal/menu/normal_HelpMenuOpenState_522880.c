/* rgp:protos */
#define RGP_SELF_normal_HelpMenuOpenState_522880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00522880 -- the 0x28/0x29/0x2A/0x2B/0x2C widget group's one-shot
 * setup, then a per-frame poll on 0x2A's fade value.
 * ⚠ `$4` is never read: the first parameter leaves no trace.  This is one of
 * the state-handler family (see normal_TransSaveQuitState_51a020) and they are all f(void*, s32).
 * `sw $0, -0x76C($28)` rides in normal_HelpMenuScrollBarLayout_522b90's delay slot, so the
 * zeroing store is written BEFORE the call in source. */

extern u8 normal_D_00528180;

extern f32 D_0047D7CC;            /* gp - 0x79A4 */
extern f32 D_00484A04;            /* gp - 0x76C  */
extern s32 D_004849F0;            /* gp - 0x780  */
extern s32 D_004849B4;            /* gp - 0x7BC  */
extern s32 D_004849A8;            /* gp - 0x7C8  */

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

s32 normal_HelpMenuOpenState_522880(void *a, s32 b)
{
    s32 i;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(&normal_D_00528180, 0x2A, 1, 1);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x2A, 0x50, 0x70);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 0x2A, D_0047D7CC);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 0x2A, 1.0f, D_0047D7CC, -1.0f);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x29, 0x52, 0x70);
        UiSetWidgetsVisibleById_291110(&normal_D_00528180, 0x29, 1, 1);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 0x29, D_0047D7CC);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 0x29, 1.0f, D_0047D7CC, -1.0f);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x2C, -0x1A, 6);
        i = 0;
        do {
            UiSetSpriteW_28fbf0(&normal_D_00528180, 0x2A, 0x14F, i);
            UiSetSpriteUvW_28f850(&normal_D_00528180, 0x2A, 4, i);
            i += 1;
        } while (i < 8);
        D_00484A04 = 0.0f;
        D_00484A04 = normal_HelpMenuScrollBarLayout_522b90(0x2B, 0xD8, 8, D_004849F0);
        UiSetSpriteUv_28f970(&normal_D_00528180, 0x2B, 0x80, 0x4C, 0);
        UiSetSpriteUv_28f970(&normal_D_00528180, 0x2B, 0x80, 0x52, 1);
        UiSetSpriteUv_28f970(&normal_D_00528180, 0x2B, 0x80, 0x5A, 2);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x2B, 0x154, 3);
        normal_HelpMenuListFill_522e30(0);
        UiSetWidgetsVisibleById_291110(&normal_D_00528180, 0x28, 1, 1);
        UiSetTextString_28f510(&normal_D_00528180, 0x28, MsgTableLookup_28aa30(D_004849B4, 8), 0);
        UiSetTextCenteredX_28f300(&normal_D_00528180, 0x28, 0x100, 0);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x28, 0, 0x14);
        UiSetWidgetAlpha_2907a0(&normal_D_00528180, 0x28, D_0047D7CC);
        UiFadeWidgetAlpha_290690(&normal_D_00528180, 0x28, 1.0f, D_0047D7CC, -1.0f);
        UiSetSpriteW_28fbf0(&normal_D_00528180, 0x2A, 0, 0);
        UiSetSpriteUvW_28f850(&normal_D_00528180, 0x2A, 0, 0);
        UiSetWidgetPos_290f60(&normal_D_00528180, 0x29, 0x52, 0x70);
    }
    if (!(UiGetWidgetAlpha_290770(&normal_D_00528180, 0x2A) < 1.0f)) {
        StateMachineSetState_28ede0(&D_004849A8, 0x7538, 1);
    }
    return 1;
}
