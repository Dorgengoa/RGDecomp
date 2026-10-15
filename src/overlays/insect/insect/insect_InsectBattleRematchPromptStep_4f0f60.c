#include "types.h"
/* insect 0x004F0F60 -- 1,196 bytes, 299 instructions, 42 calls, 13 conditional
 * branches, br/ins 0.043.  A phase driver for the 0xC37x/0xC38F/0xC39x widget
 * set, dispatched through a real 6-entry jump table (jtbl_00524BB0) on the s8
 * phase counter o->f5FC2.
 *
 * ★ THE TABLE IS BIASED: `addiu $2, $4, 0x1` before `sltiu $1, $2, 0x6`, so the
 * case set is -1..4, not 0..5 (insect-jump-table-density).  Case 2 FALLS
 * THROUGH into case 3, which is why the two blocks are adjacent; block order is
 * ascending, i.e. source order, so the reversed-compare-chain rule does not
 * apply here.  The range check's `beql` carries `lw $4, 0x87C($17)` -- the
 * shared tail's own first instruction -- so there is no `default:` arm.
 *
 * st is a named local because cases -1 and 2 REUSE the switch's own loaded
 * value (`addiu $2, $4, 0x1` with no `lb`), while cases 0, 1 and 3 re-read the
 * member because a call sits between.  Writing all five off the member gives
 * two extra loads; writing all five off `st` keeps it live across the calls.
 *
 * o->f4F90 and o->f506C are REMATERIALISED at every site (bare
 * `addiu $4, $17, K`) so they are array members; the 0x5054 and 0x5F82
 * addresses are both HOISTED into $16 and are locals --
 * insect-array-member-blocks-cse, both halves in one function.
 *
 * D_0047D88C is a gp float constant (_gp 0x00485170 - 0x78E4), so it must stay
 * NON-const to keep %gp_rel.
 */

typedef struct Ins {
    u8    pad000[0x87C];
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x506C - 0x4FBD];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    s32   f5DA8;                /* +0x5DA8 */
    u8    pad5DAC[0x5EF4 - 0x5DAC];
    s32   f5EF4;                /* +0x5EF4 */
    u8    pad5EF8[0x5FC2 - 0x5EF8];
    s8    f5FC2;                /* +0x5FC2 */
    s8    f5FC3;                /* +0x5FC3 */
    s8    f5FC4;                /* +0x5FC4 */
} Ins;

extern f32 D_0047D88C;
extern const u8 D_00524160[];
extern const u8 D_00524BA8[];

extern void  func_1343B8(void *p, s32 a, s32 b);
extern void  func_134690(void *p, const u8 *t);
extern void  func_28F510(void *h, s32 id, void *p, s32 a);
extern void  func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *h, s32 id, s32 a, s32 b);
extern void *func_290460(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32   func_290770(void *h, s32 id);
extern void  func_2907A0(void *h, s32 id, f32 v);
extern void  func_2913A0(void *h);
extern void  func_392B20(void *g, void *w, s32 v);
extern void  func_392BB0(void *g, void *w, s32 a, s32 b, s32 c);
extern void  func_3938F0(void *g, void *w, f32 a, f32 b);

extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d);
extern void  insect_InsectCursorSetInput_511090(void *a);
extern void  insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *x, s32 *y);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern s32   insect_InsectMsgTextWidth_512ab0(void *a, void *b, s32 c);
extern s32   insect_InsectMsgGet_512b70(void *a, s32 k);

void insect_InsectBattleRematchPromptStep_4f0f60(Ins *o)
{
    s32 x4C;
    s32 x48;
    s32 v;
    void *g;
    void *p;
    s32 k;
    s32 n;
    s8  st;
    s8  t;
    s32 w;
    u8  b;
    u8  c;

    g = (u8 *)o + 0x5054;
    if (insect_InsectBattleTestFlag_50da40(o, 0x18) != 0) {
        st = o->f5FC2;
        switch (st) {
        case -1:
            o->f5FC2 = st + 1;
            break;
        case 0:
            insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, 0x2B);
            o->f4FBC |= 0x10;
            o->f5FC2 = o->f5FC2 + 1;
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524160, 1);
            if (insect_InsectBattleTestFlag_50da40(o, 0x3E) != 0 && o->f5DA8 == 4) {
                func_2907A0(o->f87C, 0xC38F, 0.0f);
                func_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
                func_392BB0(g, func_290460(o->f87C, 0xC390), 0x140, 0x30, 0);
                func_3938F0(g, func_290460(o->f87C, 0xC391), 316.0f, 44.0f);
                p = (u8 *)o + 0x5F82;
                func_1343B8(p, insect_InsectMsgGet_512b70(o->f506C, 0x2D), o->f5EF4);
                if (insect_InsectBattleTestFlag_50da40(o, 0) != 0) {
                    func_134690(p, D_00524BA8);
                }
                func_28F510(o->f87C, 0xC390, p, 0);
                w = 0x140 - insect_InsectMsgTextWidth_512ab0(o->f506C, p, 2);
                func_28F5D0(o->f87C, 0xC390, w / 2, 0x10, 0);
                func_290010(o->f87C, 0xC392, 0, -1);
                func_2907A0(o->f87C, 0xC3A3, 0.0f);
            }
            break;
        case 1:
            func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            if (func_290770(o->f87C, 0xC378) >= 1.0f) {
                o->f5FC2 = o->f5FC2 + 1;
            }
            break;
        case 2:
            o->f5FC2 = st + 1;
            o->f4FBC &= 0xFD;
            /* fallthrough */
        case 3:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00524160, 0);
            insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x4C, &x48);
            func_392B20(g, func_290460(o->f87C, 0xC37B), (u8)!(x4C != 0));
            func_392B20(g, func_290460(o->f87C, 0xC37C), x4C);
            v = -1;
            k = 5;
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                v = x4C;
            } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                v = 1;
                k = 6;
            }
            if (v == -1) {
                break;
            }
            o->f5FC4 = v;
            func_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            o->f5FC2 = o->f5FC2 + 1;
            insect_InsectBattlePlaySe_4f45b0(o, k);
            break;
        case 4:
            if (func_290770(o->f87C, 0xC378) <= D_0047D88C) {
                o->f5FC2 = -1;
                t = o->f5FC4;
                o->f5FC3 = t;
                if (t == 0) {
                    n = insect_InsectBattleGetStep_50d6a0(o, 0);
                    insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, n, 0, -1);
                }
                insect_InsectBattleClearFlag_50da90(o, 0x4E);
                o->f4FBC &= 0xEF;
            }
            break;
        }
        func_2913A0(o->f87C);
        insect_InsectCursorSetInput_511090(o->f4F90);
        b = o->f4FBC;
        c = (b & 0x10) != 0;
        if (c != 0) {
            o->f4FBC = b | 0x20;
            insect_InsectCursorSetInput_511090(o->f4F90);
            o->f4FBC &= 0xDF;
        }
    }
}
