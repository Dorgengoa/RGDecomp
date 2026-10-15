#include "types.h"
/* insect 0x004FDA60 -- 1,784 bytes, 446 instructions, 58 calls, 29 conditional
 * branches, br/ins 0.065.  A ten-arm state dispatch of the
 * insect_InsectBattleGetStep_50d6a0(o, 2) family, from x_large.py's large end.
 *
 * The compare CHAIN runs 3, 9, 0x12, 0x4B, 0x4A, 0x49, 4, 0x1E, 0x1B, 1 --
 * REVERSED -- so source case order is 1, 0x1B, 0x1E, 4, 0x49, 0x4A, 0x4B,
 * 0x12, 9, 3, and the ten blocks are laid out in exactly that order
 * (0x4FDB0C, 0x4FDBCC, 0x4FDCFC, 0x4FDDA4, 0x4FDDFC, 0x4FDE68, 0x4FDF70,
 * 0x4FDFF4, 0x4FE09C, 0x4FE0F8).
 *
 * Case 0x12 FALLS THROUGH into case 9: its last statement is followed by
 * `lw $4, 0x878($16)` at 0x004FE098, which is case 9's own `beql` delay slot.
 *
 * `(u8 *)o + 0x5054` and `(u8 *)o + 0x506C` are computed in the PROLOGUE,
 * before the dispatch call, and parked in $18/$17 -- so both are named locals
 * declared at the top of the body, the HOIST polarity of
 * insect-extern-handle-hoist.  `o->f4F90` by contrast is rematerialised at both
 * its sites (`addiu $4, $16, 0x4F90`) and stays an array member written inline.
 *
 * The case-1 compare uses `$18` because case 1's body opens with `ok = 1` --
 * the dispatch constant CSE'd into the arm, the family's recurring shape.
 *
 * `o->f5DA0 / 2` is the `bgez / addiu 1 / sra` SIGNED divide-by-two written out
 * in the source: four sites, and the dividend has to be signed for it to appear
 * at all.
 *
 * Case 0x49's third func_392B20 argument is `sltu / xori / andi 0xFF`, which is
 * `(u8)!x` and NOT `x == 0` -- the two idioms are different instruction
 * sequences (overlay-insect, session 13).
 *
 * The float guards are read off the compare/branch pair: `c.lt.s` + `bc1t`
 * (case 4) is `>=` with the body as the fall-through, and `c.le.s` + `bc1f`
 * (case 3) is `<=` with the body as the fall-through.
 *
 * 0x755E fits a signed 16-bit immediate and comes out `addiu`; 0xC378 and its
 * neighbours do not and come out `ori`.
 */

typedef struct Sub {
    u8  pad00[0x8];
    s16 f08;                        /* +0x08 */
    s16 f0A;                        /* +0x0A */
} Sub;

typedef struct Node {
    u8   pad00[0x20];
    Sub *f20;                       /* +0x20 */
} Node;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                     /* +0x0878 */
    void *f87C;                     /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x4FBC - 0x4F90];   /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5DA0 - 0x4FBD];
    s32   f5DA0;                    /* +0x5DA0 */
    s32   f5DA4;                    /* +0x5DA4 */
    s32   f5DA8;                    /* +0x5DA8 */
    u8    pad5DAC[0x5EF1 - 0x5DAC];
    u8    f5EF1;                    /* +0x5EF1 */
    u8    pad5EF2[0x5FC8 - 0x5EF2];
    f32   f5FC8;                    /* +0x5FC8 */
} Ins;

extern const u8 D_00523F60[];
extern s32 D_00484FA4;

extern void  func_1CEBA0(s32 a);
extern s32   func_1F5BE0(void);
extern void  func_290010(void *h, s32 id, s32 a, s32 b);
extern Node *func_290460(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32   func_290770(void *h, s32 id);
extern void  func_2907A0(void *h, s32 id, f32 a);
extern s32   func_290D30(void *h, s32 id);
extern void  func_290F50(void *h, s32 id, s32 x, s32 y, s32 z, f32 w);
extern void  func_290F60(void *h, s32 id, s32 x, s32 y);
extern void  func_392B20(void *w, void *n, s32 v);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern s32   insect_InsectBattlePopSavedStep_50d540(Ins *o, s32 k);
extern s32   insect_InsectBattlePopSavedState_50d590(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedStep_50d5e0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedState_50d5f0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleConfirmDialogOpen_50eaf0(s32 x, s32 y, void *h, s32 k);
extern void  insect_InsectPlaySe_510870(s32 k);
extern void  insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *p, s32 *q);
extern void  insect_InsectCursorSetPopPage_511ca0(void *a);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern void  insect_InsectTeamMarkAllActed_513540(void *r, s32 k);
extern s32   insect_InsectTeamAllActed_513690(void *r, s32 k);

void insect_InsectBattleMenuEndTurn_4fda60(Ins *o)
{
    s32   sp5C;
    s32   sp58;
    u8   *w;
    u8   *h;
    s32   ok;
    s32   i;
    Node *e;
    Node *n;
    Sub  *q;
    Sub  *r;
    s32   a;
    s32   b;
    s32   c;
    f32   v;
    void *g;

    w = (u8 *)o + 0x5054;
    h = (u8 *)o + 0x506C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        ok = 1;
        for (i = 0; i < 2; i++) {
            if (insect_InsectTeamAllActed_513690((u8 *)o + i * 0x994 + 0x35F8, o->f5EF1) == 0) {
                ok = 0;
                break;
            }
        }
        if (ok != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
            o->f4FBC |= 2;
            o->f4FBC |= 0x40;
        } else {
            insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
            o->f4FBC &= 0xFD;
        }
        break;
    case 0x1B:
        func_1CEBA0(func_1F5BE0());
        g = o->f878;
        v = 20.0f / o->f5FC8;
        D_00484FA4 = (s32)v;
        func_2907A0(g, 0x755E, 0.0f);
        func_290690(o->f878, 0x755E, 1.0f, 0.125f, -1.0f);
        e = func_290460(o->f878, 0x755E);
        n = func_290460(o->f878, 0x7573);
        if (n != 0) {
            q = n->f20;
            if (q != 0) {
                q->f08 = (1 - o->f5EF1) * 0x7E;
                q->f0A = 0xBC;
                if (o->f5DA8 != 0) {
                    q->f0A = 0x17C;
                }
            }
        }
        if (e != 0) {
            r = e->f20;
            if (r != 0) {
                r->f0A = (1 - o->f5EF1) * 0x20;
                if (o->f5DA8 != 0) {
                    r->f0A = r->f0A + 0x40;
                }
                insect_InsectPlaySe_510870(3);
            }
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x12, 2, -1);
        break;
    case 0x1E:
        func_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, h, 0x10);
        insect_InsectBattleSetStep_50d7a0(o, 4, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523F60, 1);
        break;
    case 4:
        if (func_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 0, -1);
            o->f4FBC &= 0xFD;
        }
        break;
    case 0x49:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &sp5C, &sp58);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523F60, 0);
        func_392B20(w, func_290460(o->f87C, 0xC37B), (u8)!sp5C);
        func_392B20(w, func_290460(o->f87C, 0xC37C), sp5C);
        break;
    case 0x4A:
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        a = insect_InsectBattleGetSavedState_50d5f0(o, 0);
        b = insect_InsectBattleGetSavedStep_50d5e0(o, 0);
        c = insect_InsectBattleGetSavedState_50d5f0(o, 2);
        if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x37);
            a = insect_InsectBattlePopSavedState_50d590(o, 0);
            b = insect_InsectBattlePopSavedStep_50d540(o, 0);
            c = insect_InsectBattlePopSavedState_50d590(o, 2);
        }
        insect_InsectBattleSetState_50d8c0(o, a, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, b, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, c, 2, -1);
        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
        break;
    case 0x4B:
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        for (i = 0; i < 2; i++) {
            insect_InsectTeamMarkAllActed_513540((u8 *)o + i * 0x994 + 0x35F8, o->f5EF1);
        }
        insect_InsectBattleSetStep_50d7a0(o, 1, 2, -1);
        break;
    case 0x12:
        func_290F60(o->f878, 0x755E, o->f5DA0 / 2, (o->f5DA4 - 0x20) / 2);
        func_290F50(o->f878, 0x755E, (o->f5DA0 - 0x100) / 2,
                    (o->f5DA4 - 0x20) / 2, 0, 0.5f);
        func_290010(o->f878, 0x755E, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 9, 2, -1);
        /* fall through */
    case 9:
        if (func_290D30(o->f878, 0x755E) == 0) {
            D_00484FA4 = D_00484FA4 - 1;
            if (D_00484FA4 <= 0) {
                func_290690(o->f878, 0x755E, 0.0f, 0.125f, -1.0f);
                insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            }
        }
        break;
    case 3:
        if (func_290770(o->f878, 0x755E) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
        }
        break;
    }
}
