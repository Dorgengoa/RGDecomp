/* rgp:protos */
#define RGP_SELF_normal_TransHunterRankOpenState_51e290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051E290 -- the 0x763F/0x764B/0x7644 panel build.  `beqz $5` at the
 * top skips straight to the shared func_28EDE0 tail; the NULL return from
 * func_28FE10 is the only `return 0`.
 * `lui 0x3F80 / sw` is a float constant STORE, not an mtc1 pair.
 * normal_FUN_0051ED00 returns f32 in $f0 and that value is reused for the
 * following multiply -- one source read of D_004848B8 after the assignment. */

typedef struct Box {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    u8  pad08[0x2];
    s16 f0A;
    u8  pad0C[0xA];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Box;

extern f32   D_0047D920;          /* gp - 0x7850 */
extern f32   D_0047D9BC;          /* gp - 0x77B4 */
extern f32   D_00480750;          /* gp - 0x4A20 */
extern f32   D_00480754;          /* gp - 0x4A1C */
extern s16   D_00480758;          /* gp - 0x4A18 */
extern s16   D_004848B4;          /* gp - 0x8BC  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484720;          /* gp - 0xA50  */

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

s32 normal_TransHunterRankOpenState_51e290(void *a, s32 b)
{
    Box *w;
    Box *h;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0xA, 0);
        w = ((Box *)UiGetWidgetSprite_28fe10(D_00484710, 0x763F, 0));
        if (w == NULL) {
            return 0;
        }
        UiLayoutPanelFrame_28d580(w, 0, 0, 0x199, 0x152, 0);
        UiSetWidgetVisible_290010(D_00484710, 0x763F, 1, -1);
        UiSetWidgetPos_290f60(D_00484710, 0x763F, 0x200, 0x49);
        UiMoveWidgetUniform_290f50(D_00484710, 0x763F, 0x4B, 0x49, D_0047D920, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x763F, 1.0f, 0.0625f, 0.0f);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x764B, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x764B, 0xCE, 0x183);
        h = ((Box *)UiEntryListFindByTag_28ea40(D_00484720, 0xA));
        D_00480754 = 1.0f;
        D_00480758 = -1;
        D_00480750 = D_0047D9BC;
        normal_TransHunterRankListFill_51d820(h->f1A);
        D_004848B8 = normal_TransHunterScrollBarLayout_51ed00(0x7644, 0x171, 0x1C, 0x117, 0xA, 0x64, 0);
        UiSetWidgetPos_290f60(D_00484710, 0x7644, 0, (s32)((f32)h->f1A * D_004848B8));
        if (D_00480758 >= 0) {
            h->f16 = D_00480758;
        }
        UiSetWidgetPos_290f60(D_00484710, 0x764A, h->f04, h->f06 + h->f16 * h->f0A);
        UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E, h->f06 + h->f16 * h->f0A, 0);
        D_004848B4 = h->f16;
    }
    StateMachineSetState_28ede0(D_0048470C, 0x1A, 0);
    return 1;
}
