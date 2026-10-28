/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyListState_50df50 1
#include "port/game_protos.h"
#line 1
/* ★★★★★★★★ SESSION 45 (n45a4): BYTE-IDENTICAL, 508/508 words, MERGED.
 * 40 bad -> 0 on FOUR statement-level edits, three of which s43 had already
 * measured and REJECTED because it scored them ONE AT A TIME.
 *
 * ⚠⚠ s43's note "THE STATEMENT-ORDER LATTICE IS EXHAUSTED: all 36 cells were
 * measured and the INSTALLED cell is the unique best (40)" was TRUE AND
 * MISLEADING.  It is true as a single edit.  Three of the four winning edits
 * score WORSE alone (`a021` alone is one word LONG; `b120` alone is 42; the
 * mode==2 swap alone is one word SHORT) and the cross of all three is 8.
 * [[levers.d/two-edit-cross-beats-count-ranking]] -- and a 6x6 lattice scored
 * cell-by-cell inside ONE block cannot see a partner in a DIFFERENT block.
 *
 * THE FOUR EDITS
 * 1. `func_3C6460 == 0` arm: `D_00484630 = 2;` BEFORE `func_28EDE0(...753E)`
 *    (retail `addiu $2,$0,0x2 | sb $2,-0xB40($28)` sit before the `jal`).
 * 2. its else arm: `D_00484644 = sl;` moved BELOW `normal_ShopMenuBuyRowIconsRefresh_50dae0` so the
 *    `bnel`'s delay slot threads `lh $4,0x16($17)` -- retail's else arm starts
 *    with the dae0 call, ours started with the store.  ⚠ It goes BETWEEN the
 *    two calls (order dae0 / sl / 28EDE0); putting it last is 8, not 6.
 * 3. mode==2: `normal_ShopMenuBuyRowHintShow_50c550(0);` BEFORE `D_0048464C = -0x3C;`, which
 *    puts the store in the `b .L0050E6B4` delay slot.
 * 4. THE LAST SIX WORDS, and the general lever:
 *      `if (h->f0E - h->f0A < (s16)v)`  ->  `if (h->f16 > h->f0E - h->f0A)`
 *    TWO facts in one token.  (a) `h->f16` was assigned `v` on the line above,
 *    so reading it BACK keeps the s16 conversion node that `(s16)v` folds --
 *    [[levers.d/mwcc-readback-carries-conversion]], 6 bad -> 4 with a cleaner
 *    census.  (b) retail evaluates that operand FIRST (`dsll32 $3,$2,16` ahead
 *    of `lh $4,0xA($17)`), so the comparison is written with the readback on
 *    the LEFT.  Neither half closes alone.
 *    ⚠ MEASURED INERT: every spelling of the OLD `(s16)v` guard -- operand
 *    swap, `!(<=)`, extra parens, `(s32)(s16)v`, a named `sub`/`sv`/`a0` temp,
 *    `v` as s16, and `(s16)h->f16 +` in the assignment.  `v` as u16 or s64,
 *    `sub <= v-1` and `-(f0A - f0E)` are all LENGTH-WRONG.
 *    ⚠ `!(h->f16 <= ...)` and an extra paren pair are the SAME OBJECT as the
 *    installed form; the operand ORDER is the lever, not the operator.
 *
 * s43's two independent edits (`u8 changed` + the bare truth test; the mode==2
 * guard reversal and arm swap) are still installed and still required. */
#include "types.h"
/* normal 0x0050DF50 -- the 0x4B2570 shop/list page's per-frame scroll driver.
 * Second parameter non-zero re-seeds the panel from normal_D_00527D30; then
 * func_28E170's mode selects: 1 = commit the highlighted row, 2 = the close
 * animation, anything else = the L1/R1/up/down page walk.  Every walk arm ends
 * in the same `if (changed)` re-seed at 0x0050E6B4.
 * Session 31 lane a7, FRESH unit. */

typedef struct H {
    u8  pad00[0x2];
    s16 f02;
    u8  pad04[0x6 - 0x4];
    s16 f06;
    u8  pad08[0xA - 0x8];
    s16 f0A;
    u8  pad0C[0xE - 0xC];
    s16 f0E;
    u8  pad10[0x12 - 0x10];
    s16 f12;
    u8  pad14[0x16 - 0x14];
    s16 f16;
} H;

typedef struct W {
    u8  pad00[0x14];
    s16 f14;
    s16 f16;
    u8  pad18[0x1A - 0x18];
    s16 f1A;
} W;

typedef struct Desc {
    s16 f00;
    u8  pad02[0x14 - 0x2];
    s8  f14;
} Desc;

typedef struct Ent {
    u8    pad00[0x10];
    Desc *f10;
} Ent;

typedef struct M {
    u8  pad00[0x14];
    s32 f14;
} M;

typedef struct Q {
    u8 pad00[0x6];
    u8 f06;
} Q;

typedef struct SL {
    Ent *f00;
    Q   *f04;
} SL;

typedef struct GD {
    u8  pad000[0x160];
    s64 f160;
} GD;

typedef struct G {
    u8  pad00[0x18];
    GD *f18;
} G;

extern u8 D_004B2570;
extern SL      *normal_D_00527D30[];

extern M    *D_004845D0;   /* gp - 0xBA0 */
extern void *D_004845C8;   /* gp - 0xBA8 */
extern void *D_004845CC;   /* gp - 0xBA4 */
extern void *D_004845C4;   /* gp - 0xBAC */
extern s32   D_0048464C;   /* gp - 0xB24 */
extern s16   D_0048463C;   /* gp - 0xB34 */
extern s16   D_00484638;   /* gp - 0xB38 */
extern f32   D_00484634;   /* gp - 0xB3C */
extern u8    D_00484630;   /* gp - 0xB40 */
extern SL   *D_00484644;   /* gp - 0xB2C */
extern f32   D_0047D4C4;   /* gp - 0x7CAC */
extern f32   D_0047D488;   /* gp - 0x7CE8 */
extern f32   D_0047D470;   /* gp - 0x7D00 */
extern f32   D_0047D460;   /* gp - 0x7D10 */

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

s32 normal_ShopMenuBuyListState_50df50(s32 arg0, s32 seed)
{
    W    *w;
    SL   *s0;
    s32   mode;
    H    *h;
    SL   *sl;
    u8    changed;
    G    *g;
    Ent  *e;
    s8    c;
    s8    flag;
    s64   v160;
    s32   v;
    SL   *s2;

    if (seed != 0) {
        UiEntryListSelectByTag_28ea90(D_004845D0, 0x7532, 0);
        UiFadeWidgetAlpha_290690(D_004845C8, 0x2F, 1.0f, D_0047D4C4, -1.0f);
        ((W *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7533))->f14 = 0;
        w = ((W *)UiEntryListFindByTag_28ea40(D_004845D0, 0x7532));
        s0 = normal_D_00527D30[w->f16 + w->f1A];
        if (s0 == 0) {
            return 0;
        }
        normal_ShopMenuRowInfoShow_509460(s0, D_0047D488, 0x34, 0x33, 0x56, 0x15E);
        D_0048464C = 0;
        D_0048463C = 0;
        normal_ShopMenuBuyRowHintShow_50c550(0);
    }
    mode = MenuGridCursorInput_28e170(D_004845D0, &D_004B2570, 0, 0);
    h = ((H *)UiEntryListGetCurrentData_28ec60(D_004845D0));
    sl = normal_D_00527D30[h->f12 + h->f16];
    changed = 0;
    if (mode == 1) {
        if (normal_ShopMenuRowIsBuyable_50b570(sl) != 0) {
            g = ((G *)GetGameData_1fede0());
            e = sl->f00;
            c = e->f10->f14;
            flag = 0;
            if (c >= 0) {
                flag = c;
            }
            InvCountById_3c78d0(g->f18, e->f10->f00, flag, 0);
            if ((sl->f04->f06 & 1) && InvHasItemInCategory_3c7f40(g->f18, 0x40FB, 0xA, 0) == 0) {
                normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                D_00484630 = 0xC;
                StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
            } else {
                v160 = g->f18->f160;
                if (v160 < (s64)ShopRowGetPrice_3ce6e0(sl)) {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484630 = 1;
                    StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
                } else if (InvAddItemCheckedMaybe_3c6460(g->f18, e->f10->f00, 1, flag, 0) == 0) {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484630 = 2;
                    StateMachineSetState_28ede0(D_004845C4, 0x753E, 0);
                } else {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484644 = sl;
                    StateMachineSetState_28ede0(D_004845C4, 0x7538, 0);
                }
            }
            normal_ShopMenuBuyRowHintShow_50c550(0);
        }
    } else if (mode == 2) {
        if (UiGetWidgetAlpha_290770(D_004845CC, 0x50) > D_0047D470) {
            normal_ShopMenuBuyRowHintShow_50c550(0);
            D_0048464C = -0x3C;
        } else {
            StateMachineSetState_28ede0(D_004845C4, 0x7536, 0);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x50, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x74, 0, 1);
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x75, 0, 1);
        }
    } else if (PadIsTriggered_1839f0(&D_004B2570, 0x8000) != 0) {
        if (h->f12 > 0 || h->f16 > 0) {
            MenuGridCursorRequestSe_28e9e0(D_004845D0, 0);
            changed = 1;
        }
        if (h->f16 > 0) {
            v = h->f16 - (s16)(h->f0A + 1);
            h->f16 = v;
            if ((s16)v < 0) {
                h->f16 = 0;
                h->f12 = 0;
                UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02, 0);
            }
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
        } else {
            h->f16 = 0;
            h->f12 = 0;
            UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02, 0);
        }
        if (h->f16 < 0) {
            h->f16 = 0;
        }
        UiMoveWidgetUniform_290f50(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634), D_0047D460, 0);
    } else if (PadIsTriggered_1839f0(&D_004B2570, 0x2000) != 0) {
        if (h->f12 < h->f0A || h->f16 < h->f0E - h->f0A) {
            MenuGridCursorRequestSe_28e9e0(D_004845D0, 0);
            changed = 1;
        }
        if (h->f16 < h->f0E - h->f0A) {
            v = h->f16 + (s16)(h->f0A + 1);
            h->f16 = v;
            if (h->f16 > h->f0E - h->f0A) {
                h->f12 = h->f0A;
                h->f16 = h->f0E - h->f0A;
                UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            }
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
        } else {
            h->f12 = h->f0A;
            h->f16 = h->f0E - h->f0A;
            UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
        }
        if (h->f16 < 0) {
            h->f16 = 0;
        }
        UiMoveWidgetUniform_290f50(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634), D_0047D460, 0);
    } else if ((D_004845D0->f14 & 1) && PadIsTriggered_1839f0(&D_004B2570, 0x1000) != 0
               && PadIsRepeatTriggered_183dd0(&D_004B2570, 0x1000) == 0) {
        if (h->f12 == 0 && h->f16 == 0 && h->f0E > 0) {
            MenuGridCursorRequestSe_28e9e0(D_004845D0, 0);
            h->f12 = h->f0A;
            changed = 1;
            h->f16 = h->f0E - h->f0A;
            UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
            UiSetWidgetPos_290f60(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634));
        }
    } else if ((D_004845D0->f14 & 2) && PadIsTriggered_1839f0(&D_004B2570, 0x4000) != 0
               && PadIsRepeatTriggered_183dd0(&D_004B2570, 0x4000) == 0) {
        if (h->f12 == h->f0A && h->f16 == h->f0E - h->f0A && h->f0E > 0) {
            MenuGridCursorRequestSe_28e9e0(D_004845D0, 0);
            h->f12 = 0;
            h->f16 = 0;
            changed = 1;
            UiSetSpriteY_28fc90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
            UiSetWidgetPos_290f60(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634));
        }
    }
    if (changed) {
        s2 = normal_D_00527D30[h->f12 + h->f16];
        if (s2 == 0) {
            return 0;
        }
        normal_ShopMenuRowInfoShow_509460(s2, D_0047D488, 0x34, 0x33, 0x56, 0x15E);
        D_00484638 = h->f12;
        D_0048464C = 0;
        normal_ShopMenuBuyRowHintShow_50c550(0);
    }
    return 1;
}
