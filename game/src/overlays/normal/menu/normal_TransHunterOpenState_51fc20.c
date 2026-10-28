/* rgp:protos */
#define RGP_SELF_normal_TransHunterOpenState_51fc20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051FC20 -- the 0x7553 panel's fade state machine.  gp-0x8C4 is the
 * phase (-1 = build, 0 = fade in, 1 = fade out) and gp-0x8C0 is its 0..1
 * alpha.  The three phases are a SWITCH: retail emits the compares in reverse
 * case order (1, 0, -1) with the bodies in source order, and the no-case path
 * branches straight to the tail with the alpha load duplicated into its delay
 * slot. */

typedef struct Rec {
    u8  pad00[4];
    s16 f04;
    s16 f06;
    u8  pad08[0xE - 8];
    s16 f0E;
    u8  pad10[2];
    s16 f12;
} Rec;

typedef struct Inner { u8 pad000[0x180]; s32 f180; } Inner;
typedef struct Root  { u8 pad00[8]; void *f08; u8 pad0C[0x18 - 0xC]; Inner *f18; } Root;

extern f32   D_004848B0;          /* gp - 0x8C0  */
extern s32   D_004848AC;          /* gp - 0x8C4  */
extern s16   D_004848B4;          /* gp - 0x8BC  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern s32   D_004848BC;          /* gp - 0x8B4  */
extern s16   D_004848C0;          /* gp - 0x8B0  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484720;          /* gp - 0xA50  */
extern void *D_00484770;          /* gp - 0xA00  */
extern u8    D_0048472C;          /* gp - 0xA44  */
extern f32   D_0047D9D0;          /* gp - 0x77A0 */
extern f32   D_0047D9D8;          /* gp - 0x7798 */
extern f32   D_0047D920;          /* gp - 0x7850 */
extern f32   D_0047D9A8;          /* gp - 0x77C8 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */

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

s32 normal_TransHunterOpenState_51fc20(void *unused, s32 init)
{
    Root *t;
    Rec  *r;
    void *pane;
    s32   n;
    f32   a;
    f32   v;

    if (init != 0) {
        D_004848B0 = 0.0f;
        D_004848AC = -1;
    }
    switch (D_004848AC) {
    case -1:
        t = ((Root *)GetGameData_1fede0());
        if (WorldDataMgrNoRequestPending_3eef10(t->f08) != 0) {
            UiSlideInWidgetPair_28d010(0x753D, 0x7538, D_00484710);
            UiSetWidgetAlpha_2907a0(D_00484710, 0x7541, 1.0f);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7553, 1.0f, D_0047D9D0, -1.0f);
            D_0048472C = 0;
            UiFadeWidgetAlpha_290690(D_00484710, 0x75D1, 0.0f, D_0047D9D8, -1.0f);
            pane = UiGetWidgetSprite_28fe10(D_00484710, 0x7633, 0);
            if (pane == NULL) {
                return 0;
            }
            UiLayoutPanelFrame_28d580(pane, 0, 0, 0x19C, 0x15E, 0);
            UiSetWidgetVisible_290010(D_00484710, 0x7633, 1, -1);
            UiSetWidgetPos_290f60(D_00484710, 0x7633, 0x200, 0x49);
            UiMoveWidgetUniform_290f50(D_00484710, 0x7633, 0x49, 0x49, D_0047D920, 0);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7633, 1.0f, 0.0625f, 0.0f);
            UiSetWidgetAlpha_2907a0(D_00484710, 0x7637, 0.0f);
            UiSetWidgetAlpha_2907a0(D_00484710, 0x764D, 0.0f);
            UiSetWidgetAlpha_2907a0(D_00484710, 0x7638, 0.5f);
            r = ((Rec *)UiEntryListFindByTag_28ea40(D_00484720, 9));
            UiSetWidgetPos_290f60(D_00484710, 0x764D, r->f04, r->f06);
            UiSetSpriteY_28fc90(D_00484710, 0x7637, r->f06, 0);
            UiSetTextString_28f510(D_00484710, 0x763C, MsgTableLookup_28aa30(D_00484770, 0), 0);
            UiSetTextString_28f510(D_00484710, 0x763C, MsgTableLookup_28aa30(D_00484770, 1), 1);
            UiSetWidgetSubItemValue_291250(D_00484710, 0x763C, 1, (long long)(t->f18->f180));
            n = normal_TransHunterBountyListFill_51efe0(0);
            D_004848B8 = normal_TransHunterScrollBarLayout_51ed00(0x763E, 0x174, 0x1E, 0xE3, 8, n, 0);
            UiSetWidgetPos_290f60(D_00484710, 0x763E, 0, 0);
            if (n < 9) {
                r->f0E = n - 1;
                r->f12 = n - 1;
            } else {
                r->f0E = 7;
                r->f12 = n - 1;
            }
            D_004848B4 = 0;
            D_004848AC = 0;
        }
        break;
    case 0:
        v = D_004848B0 + D_0047D9A8;
        D_004848B0 = v;
        if (!(v < D_0047D35C)) {
            D_004848B0 = D_0047D35C;
            D_004848AC = 1;
        }
        break;
    case 1:
        D_004848B0 = D_004848B0 - D_0047D9A8;
        break;
    }
    a = D_004848B0;
    UiSetWidgetColor_2905b0(D_00484710, 0x7553, a, a, a, 1.0f);
    if (D_004848B0 <= 1.0f) {
        if (D_004848AC == 1) {
            n = normal_TransHunterBountyListFill_51efe0(0);
            D_004848B0 = 1.0f;
            UiSetWidgetColor_2905b0(D_00484710, 0x7553, 1.0f, 1.0f, 1.0f, 1.0f);
            if (n == 0) {
                D_004848BC = 2;
                D_004848C0 = 0x12;
                StateMachineSetState_28ede0(D_0048470C, 0x13, 0);
            } else {
                UiSetWidgetsVisibleById_291110(D_00484710, 0x764B, 1, 1);
                UiSetWidgetPos_290f60(D_00484710, 0x764B, 0xCE, 0x18F);
                UiEntryListSelectByTag_28ea90(D_00484720, 9, 1);
                StateMachineSetState_28ede0(D_0048470C, 0x11, 0);
            }
        }
    }
    return 1;
}
