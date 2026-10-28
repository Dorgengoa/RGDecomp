/* rgp:protos */
#define RGP_SELF_normal_ShopMenuTopState_509a80 1
#include "port/game_protos.h"
#line 1
/* ag9a80 (session 33): CLOSED, byte-identical.  The $2/$3 exchange that
 * parked this at 14 for many sessions was mwcc's SCHEDULER, not the register
 * allocator: retail interleaves the `id = i + 9` addiu into the MIDDLE of the
 * `y = i * 0x26` shift/add chain (source-position-driven, like the vreg
 * creation order lever), and in the first loop-body call it ALSO defers the
 * `v = 0.02f*i; v = 0.35f-v;` float statements to AFTER that chain and the
 * call's integer argument setup instead of before it -- moving the float pair
 * down past the `t`/`id`/`y` computation closed the last 3-word argument-order
 * residue at 0x00509B6C.  Splitting `y = i * 0x26` into its own statements
 * with `id = i + 9` textually inserted between the *8+i step and the *2+i
 * step reproduces retail's mid-chain interleave for BOTH occurrences (the
 * loop body and the `k` tail), even though the two occurrences differ in
 * exactly where in the 5-op chain the interleave falls (after the first
 * shift for the `k` block, after the first add+shift for the loop body). */
#include "types.h"
/* normal 0x00509A80 -- the 0x7531 dialog's open, its two-row layout loop and
 * the answer poll.  Widget ids are u16 (`andi $5, $rX, 0xFFFF` at every call).
 * The `mul.s` / `sub.s` in the loop is NOT contracted, so the product is its
 * own statement ([[normal-madd-contraction]]).
 * m2c renders the last dispatch as an irregular `switch`; the listing is a
 * `beql`/`beql` compare CHAIN testing 1 before 0 -- but mwcc normalises the
 * order, so `case 0` must come FIRST in the source to get retail's dispatch.
 *
 * CLOSED (session 33/ag9a80): see the mechanism note above the #include. */

extern u8 normal_D_005264C0;
extern u8 normal_D_005264D0;
extern u8 D_004B2570[0x10];       /* main-image object; an ADDRESS, and the
                                     size keeps it out of small data */

/* the panel objects must be OVER the small-data threshold or every reference
 * comes out GPREL16 instead of retail's lui/%lo -- 20 words short. */
typedef struct Panel { u8 pad000[0x40]; } Panel;
extern Panel normal_D_00527C40;
extern Panel normal_D_00527C80;

typedef struct Rec {
    u8   pad000[0x12];
    s16  f012;
} Rec;

typedef struct Wid {
    u8   pad000[0x20];
    void *f020;
} Wid;

typedef struct Box {
    u8   pad000[4];
    s16  f004;
    s16  f006;
    u8   pad008[4];
    s16  f00C;
    s16  f00E;
} Box;

extern s16   D_00484600;          /* gp - 0xB70 */
extern s16   D_00484604;          /* gp - 0xB6C */
extern s16   D_004845B8;          /* gp - 0xBB8 */

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

s32 normal_ShopMenuTopState_509a80(void *a, s32 b)
{
    s32 i;
    s32 y;
    f32 v;
    Rec *w;
    s32 r;
    s16 k;
    Box *bx;
    s32 t;
    s32 id;

    if (b != 0) {
        TaskSetCharaTasksPaused_288130(1);
        TaskSetEnabled_27c2a0(0, &normal_D_005264C0);
        TaskSetEnabled_27c2a0(0, &normal_D_005264D0);
        UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 0x30, 1, 1);
        UiSetWidgetPos_290f60(&normal_D_00527C40, 0x30, 0x26, 0x6A);
        UiSetWidgetAlpha_2907a0(&normal_D_00527C40, 0x30, 0.0f);
        UiFadeWidgetAlpha_290690(&normal_D_00527C40, 0x30, 1.0f, 0.05f, -1.0f);
        UiEntryListSelectByTag_28ea90(&normal_D_00527C80, 0x7531, 0);
        i = 0;
        do {
            /* product and difference in the SAME variable: written as two
             * variables mwcc contracts this into adda.s/msub.s and retail has
             * plain mul.s/sub.s.  15 other spellings measured, incl. volatile
             * and every operand order -- only reusing the destination works. */
            t = i * 8;
            id = i + 9;
            t = t + i;
            t = t * 2;
            t = t + i;
            y = t * 2;
            v = 0.02f * (f32)i;
            v = 0.35f - v;
            UiMoveWidgetUniform_290f50(&normal_D_00527C40, (u16)id, 0x21, y + 0x32, v, 0);
            UiMoveWidgetUniform_290f50(&normal_D_00527C40, (u16)(i + 6), 0x24, y + 0x35, v, 0);
            UiSetWidgetsVisibleById_291110(&normal_D_00527C40, (u16)(i + 0xB), 1, 1);
            i += 1;
        } while (i < 2);
        k = ((Rec *)UiEntryListGetCurrentData_28ec60(&normal_D_00527C80))->f012;
        t = k * 8;
        id = k + 9;
        t = t + k;
        t = t * 2;
        t = t + k;
        y = t * 2;
        UiMoveWidgetUniform_290f50(&normal_D_00527C40, (u16)id, 0x2B, y + 0x32, 0.35f, 0);
        UiMoveWidgetUniform_290f50(&normal_D_00527C40, (u16)(k + 6), 0x2E, y + 0x35, 0.35f, 0);
        D_00484600 = 0;
        normal_ShopMenuMoneyRefresh_50ac80(0x15, 0x14);
        UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 0x11, 1, 1);
        UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 0x10, 1, 1);
        UiMoveWidgetUniform_290f50(&normal_D_00527C40, 0x11, 0x104, 0x12, 0.2f, 0);
        UiMoveWidgetUniform_290f50(&normal_D_00527C40, 0x10, 0x107, 0x15, 0.2f, 0);
        UiSetWidgetColor_2905b0(&normal_D_00527C40, 0x10, 0.0f, 0.0f, 0.0f, 0.4f);
        UiSetWidgetVisible_290010(&normal_D_00527C40, 0x1A, 0, -1);
    }
    if (D_00484600 == 0) {
        r = MenuGridCursorInput_28e170(&normal_D_00527C80, D_004B2570, 4, 0);
        w = ((Rec *)UiEntryListGetCurrentData_28ec60(&normal_D_00527C80));
        if (r == 1) {
            if ((ShopListGetRowCount_3e7e10(((s32)GetGameData_1fede0())) == 0) && (w->f012 == 0)) {
                return 0;
            }
            D_00484600 = 1;
            UiSetWidgetColor_2905b0(&normal_D_00527C40, 0xE, 1.0f, 1.0f, 1.0f, 1.0f);
            UiFadeWidgetAlpha_290690(&normal_D_00527C40, 0x30, 0.0f, -0.05f, -1.0f);
            D_00484604 = w->f012;
        } else if (r == 2) {
            StateMachineSetState_28ede0(&D_004845B8, 0x7533, 1);
        }
    }
    normal_ShopMenuTopPickAnimStep_509e90();
    if (D_00484600 == 7) {
        D_00484600 = 0;
        bx = ((Wid *)UiFindWidget_290460(&normal_D_00527C40, (u16)(D_00484604 + 9)))->f020;
        bx->f004 = 0x70;
        bx->f006 = 0x1B;
        bx->f00E = 4;
        bx->f00C = 4;
        switch (D_00484604) {
        case 0:
            StateMachineSetState_28ede0(&D_004845B8, 0x7534, 1);
            break;
        case 1:
            StateMachineSetState_28ede0(&D_004845B8, 0x7542, 1);
            break;
        }
    }
    return 1;
}
