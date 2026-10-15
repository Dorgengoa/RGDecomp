#include "types.h"
/* insect 0x004FC1F0 -- 1,420 bytes, 355 instructions, 49 calls, 16 conditional
 * branches, br/ins 0.045.  Chain 0x25,0x24,0x23,0x22,0x1C,0x1B,9,1 REVERSED is
 * the block layout 1,9,0x1B,0x1C,0x22,0x23,0x24,0x25, with three fall-through
 * pairs (0x1B->0x1C, 0x22->0x23, 0x24->0x25); in each pair the SECOND case's
 * test is the one that keeps its `beql`, the first is a plain `beq`.
 *
 * The width max at 0x004FC34C is the `$at` compare class ([[at-compare-class]]):
 * `slt $1, $2, $18` feeding `bnel`.  The natural `if (w >= maxw)` puts the
 * compare in a GPR; the operand-swapped `if (maxw <= w)` -- same predicate,
 * same instruction -- is what puts it in `$1`.  x_at.py flags this site.
 */

typedef struct Card {
    u8 pad00[0x18];
    s8 f18;                     /* +0x18 */
    u8 pad19[0x38 - 0x19];
    s8 f38;                     /* +0x38 */
    s8 f39;                     /* +0x39 */
} Card;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    pad4FBC[0x5B28 - 0x4FBC];
    Card *f5B28;                /* +0x5B28 */
    u8    pad5B2C[0x5EF1 - 0x5B2C];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern const u8 D_00524020[];

extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern s32   insect_InsectMsgTextWidth_512ab0(void *a, s32 b, s32 c);
extern s32   insect_InsectAbilityTableGetMatchCount_51cee0(void *a);
extern s32  *insect_InsectAbilityTableCollect_51cef0(void *a, s8 b, s8 c, s8 d, s32 e);

extern void func_28F510(void *h, s32 id, s32 a, s32 b);
extern void func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern s32  func_290460(void *h, s32 id);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);
extern void func_2907A0(void *h, s32 id, f32 v);
extern void func_290A40(void *h, s32 id, s32 rgba, s32 i);
extern s32  func_290D30(void *h, s32 id);
extern void func_290F50(void *h, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void func_290F60(void *h, s32 id, s32 a, s32 b);
extern void func_290FC0(void *h, s32 id, s32 *a, s32 *b);
extern void func_392250(void *g, s32 a, s32 b, s32 c, s32 n, s32 e,
                        s32 f, s32 h);
extern void func_3934D0(void *g, s32 w, s32 a, s32 b, s32 c, s32 d);
extern void func_393960(void *g, s32 w, s32 n);

void insect_InsectBattleMenuSpecialList_4fc1f0(Ins *o)
{
    s32 x9C;
    s32 x98;
    s32 x94;
    s32 x90;
    s32 x8C;
    s32 x88;
    s32 x84;
    s32 x80;
    void *g;
    void *p17;
    Card *e;
    s32 *tp;
    s32 *tbl;
    s32 n;
    s32 i;
    s32 maxw;
    s32 j;
    s32 w;
    s32 dx;

    g = (u8 *)o + 0x5054;
    e = o->f5B28;
    p17 = (u8 *)o + 0x50E8;
    if (e != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
        case 1:
            tbl = insect_InsectAbilityTableCollect_51cef0(p17, e->f38, e->f39, e->f18, 1);
            n = insect_InsectAbilityTableGetMatchCount_51cee0(p17);
            i = 0;
            do {
                func_28F510(o->f878, 0x7584, 0, i);
                i++;
            } while (i < 5);
            maxw = 0x7C;
            j = 0;
            while (j < n) {
                func_28F5D0(o->f878, 0x7584, 6, (j << 5) + 8, j);
                tp = tbl + j;
                func_28F510(o->f878, 0x7584, *tp, j);
                func_290A40(o->f878, 0x7584, 0xFF7F7F7F, j);
                w = insect_InsectMsgTextWidth_512ab0((u8 *)o + 0x506C, *tp, 2) + 0x10;
                if (maxw <= w) {
                    maxw = w;
                }
                j++;
            }
            func_393960(g, func_290460(o->f878, 0x7584), 5);
            func_392250(g, func_290460(o->f878, 0x7581),
                        func_290460(o->f878, 0x7584),
                        func_290460(o->f878, 0x7582), n, 1, maxw, o->f5EF1);
            func_3934D0(g, func_290460(o->f878, 0x7583), maxw - 4, 0x20, 5,
                        o->f5EF1);
            dx = 0x70;
            if (o->f5EF1 == 1) {
                dx = -(maxw + 4);
            }
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 4, &x9C, &x98);
            func_290FC0(o->f878, 0x7560, &x94, &x90);
            func_290F60(o->f878, 0x7580, x94, x90 + (x98 << 5));
            func_290F50(o->f878, 0x7580, x94 + dx, x90 + (x98 << 5), 0, 0.5f);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524020, 1);
            func_2907A0(o->f878, 0x7580, 0.0f);
            func_290690(o->f878, 0x7580, 1.0f, 0.125f, -1.0f);
            func_290010(o->f878, 0x7580, 1, -1);
            insect_InsectBattleSetStep_50d7a0(o, 9, 2, -1);
            break;
        case 9:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524020, 1);
            if (func_290D30(o->f878, 0x7580) == 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            }
            break;
        case 0x1B:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524020, 1);
            func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
            /* fallthrough */
        case 0x1C:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524020, 0);
            break;
        case 0x22:
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 4, &x8C, &x88);
            func_290690(o->f878, 0x7580, 0.0f, 0.125f, -1.0f);
            func_290FC0(o->f878, 0x7560, &x84, &x80);
            func_290F50(o->f878, 0x7580, x84, x80 + (x88 << 5), 0, 0.5f);
            insect_InsectBattleSetStep_50d7a0(o, 0x23, 2, -1);
            /* fallthrough */
        case 0x23:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524020, 1);
            if (func_290D30(o->f878, 0x7580) == 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x22, 0, -1);
            }
            break;
        case 0x24:
            func_290690(o->f878, 0x7580, 0.0f, 0.125f, -1.0f);
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0x25, 2, -1);
            /* fallthrough */
        case 0x25:
            if (func_290770(o->f878, 0x7580) <= 0.0f) {
                insect_InsectBattleSetStep_50d7a0(o, 0x24, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            }
            break;
        }
    }
}
