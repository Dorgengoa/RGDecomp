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
 * Second parameter non-zero re-seeds the panel from D_00527D30; then
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

extern const u8 D_004B2570;
extern SL      *D_00527D30[];

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

extern void  func_28EA90(void *p, s32 id, s32 c);
extern void  func_290690(void *p, s32 id, f32 x, f32 y, f32 z);
extern W    *func_28EA40(void *p, s32 id);
extern s32   func_28E170(void *p, const u8 *b, s32 c, s32 d);
extern H    *func_28EC60(void *p);
extern void  func_28E9E0(void *p, s32 a);
extern void  func_28FC90(void *p, s32 id, s32 v, s32 c);
extern void  func_290F50(void *p, s32 id, s32 a, s32 b, s32 c, f32 f);
extern void  func_290F60(void *p, s32 id, s32 a, s32 b);
extern void  func_291110(void *p, s32 id, s32 a, s32 b);
extern f32   func_290770(void *p, s32 id);
extern void  func_28EDE0(void *p, s32 id, s32 c);
extern s32   func_1839F0(const u8 *p, s32 m);
extern s32   func_183DD0(const u8 *p, s32 m);
extern G    *func_1FEDE0(void);
extern s32   func_3C78D0(GD *p, s16 id, s8 c, s32 d);
extern s32   func_3C7F40(GD *p, s32 a, s32 b, s32 c);
extern s32   func_3CE6E0(SL *p);
extern s32   func_3C6460(GD *p, s16 id, s32 a, s8 c, s32 d);

extern s32   normal_ShopMenuRowInfoShow_509460(void *h, f32 x, s32 b, s32 c, s32 d, s32 e);
extern s32   normal_ShopMenuRowIsBuyable_50b570(void *p);
extern s32   normal_ShopMenuBuyRowsRefresh_50b5c0(s32 page);
extern s32   normal_ShopMenuBuyRowIconsRefresh_50dae0(s32 a, s32 b);
extern s32   normal_ShopMenuBuyRowHintShow_50c550(s32 a);

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
        func_28EA90(D_004845D0, 0x7532, 0);
        func_290690(D_004845C8, 0x2F, 1.0f, D_0047D4C4, -1.0f);
        func_28EA40(D_004845D0, 0x7533)->f14 = 0;
        w = func_28EA40(D_004845D0, 0x7532);
        s0 = D_00527D30[w->f16 + w->f1A];
        if (s0 == 0) {
            return 0;
        }
        normal_ShopMenuRowInfoShow_509460(s0, D_0047D488, 0x34, 0x33, 0x56, 0x15E);
        D_0048464C = 0;
        D_0048463C = 0;
        normal_ShopMenuBuyRowHintShow_50c550(0);
    }
    mode = func_28E170(D_004845D0, &D_004B2570, 0, 0);
    h = func_28EC60(D_004845D0);
    sl = D_00527D30[h->f12 + h->f16];
    changed = 0;
    if (mode == 1) {
        if (normal_ShopMenuRowIsBuyable_50b570(sl) != 0) {
            g = func_1FEDE0();
            e = sl->f00;
            c = e->f10->f14;
            flag = 0;
            if (c >= 0) {
                flag = c;
            }
            func_3C78D0(g->f18, e->f10->f00, flag, 0);
            if ((sl->f04->f06 & 1) && func_3C7F40(g->f18, 0x40FB, 0xA, 0) == 0) {
                normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                D_00484630 = 0xC;
                func_28EDE0(D_004845C4, 0x753E, 0);
            } else {
                v160 = g->f18->f160;
                if (v160 < (s64)func_3CE6E0(sl)) {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484630 = 1;
                    func_28EDE0(D_004845C4, 0x753E, 0);
                } else if (func_3C6460(g->f18, e->f10->f00, 1, flag, 0) == 0) {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484630 = 2;
                    func_28EDE0(D_004845C4, 0x753E, 0);
                } else {
                    normal_ShopMenuBuyRowIconsRefresh_50dae0(h->f16, 0);
                    D_00484644 = sl;
                    func_28EDE0(D_004845C4, 0x7538, 0);
                }
            }
            normal_ShopMenuBuyRowHintShow_50c550(0);
        }
    } else if (mode == 2) {
        if (func_290770(D_004845CC, 0x50) > D_0047D470) {
            normal_ShopMenuBuyRowHintShow_50c550(0);
            D_0048464C = -0x3C;
        } else {
            func_28EDE0(D_004845C4, 0x7536, 0);
            func_291110(D_004845CC, 0x50, 0, 1);
            func_291110(D_004845CC, 0x74, 0, 1);
            func_291110(D_004845CC, 0x75, 0, 1);
        }
    } else if (func_1839F0(&D_004B2570, 0x8000) != 0) {
        if (h->f12 > 0 || h->f16 > 0) {
            func_28E9E0(D_004845D0, 0);
            changed = 1;
        }
        if (h->f16 > 0) {
            v = h->f16 - (s16)(h->f0A + 1);
            h->f16 = v;
            if ((s16)v < 0) {
                h->f16 = 0;
                h->f12 = 0;
                func_28FC90(D_004845C8, 0x1C, h->f02, 0);
            }
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
        } else {
            h->f16 = 0;
            h->f12 = 0;
            func_28FC90(D_004845C8, 0x1C, h->f02, 0);
        }
        if (h->f16 < 0) {
            h->f16 = 0;
        }
        func_290F50(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634), 0, D_0047D460);
    } else if (func_1839F0(&D_004B2570, 0x2000) != 0) {
        if (h->f12 < h->f0A || h->f16 < h->f0E - h->f0A) {
            func_28E9E0(D_004845D0, 0);
            changed = 1;
        }
        if (h->f16 < h->f0E - h->f0A) {
            v = h->f16 + (s16)(h->f0A + 1);
            h->f16 = v;
            if (h->f16 > h->f0E - h->f0A) {
                h->f12 = h->f0A;
                h->f16 = h->f0E - h->f0A;
                func_28FC90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            }
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
        } else {
            h->f12 = h->f0A;
            h->f16 = h->f0E - h->f0A;
            func_28FC90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
        }
        if (h->f16 < 0) {
            h->f16 = 0;
        }
        func_290F50(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634), 0, D_0047D460);
    } else if ((D_004845D0->f14 & 1) && func_1839F0(&D_004B2570, 0x1000) != 0
               && func_183DD0(&D_004B2570, 0x1000) == 0) {
        if (h->f12 == 0 && h->f16 == 0 && h->f0E > 0) {
            func_28E9E0(D_004845D0, 0);
            h->f12 = h->f0A;
            changed = 1;
            h->f16 = h->f0E - h->f0A;
            func_28FC90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
            func_290F60(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634));
        }
    } else if ((D_004845D0->f14 & 2) && func_1839F0(&D_004B2570, 0x4000) != 0
               && func_183DD0(&D_004B2570, 0x4000) == 0) {
        if (h->f12 == h->f0A && h->f16 == h->f0E - h->f0A && h->f0E > 0) {
            func_28E9E0(D_004845D0, 0);
            h->f12 = 0;
            h->f16 = 0;
            changed = 1;
            func_28FC90(D_004845C8, 0x1C, h->f02 + h->f12 * h->f06, 0);
            normal_ShopMenuBuyRowsRefresh_50b5c0(h->f16);
            func_290F60(D_004845C8, 0x25, 0, (s32)(h->f16 * D_00484634));
        }
    }
    if (changed) {
        s2 = D_00527D30[h->f12 + h->f16];
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
