#include "types.h"
/* insect 0x004FF040 -- 780 bytes, 195 instructions, 29 calls, 5 conditional
 * branches.  A four-arm state dispatch.
 *
 * IT IS A `switch`, NOT A CHAIN, and the delay slots are the discriminator:
 * every converted `beql` carries the TAKEN ARM'S FIRST INSTRUCTION (the
 * `lui $2,0x3E000000` of the 0.125f constant, or the arm's own `addiu $4,...`),
 * never the next guard's constant.  The compare chain runs 0x1E, 0x1D, 0x1C, 1
 * -- REVERSED -- so source case order is ascending 1, 0x1C, 0x1D, 0x1E.  The
 * values are far too sparse for a jump table and mwcc compiles the chain.
 *
 * ★ The 0.125f in cases 0x1D and 0x1E is materialised by the DISPATCH's own
 * delay slot and reused by the first func_290690 in the arm, so the arm reads
 * one instruction short of what it needs.  An argument never materialised in
 * its own block is not a missing instruction -- write the literal and let mwcc
 * share it.
 *
 * insect_InsectBattleGetStep_50d6a0 takes TWO arguments: 0x00502004 marshals $5 and nothing
 * else, so the $6 that happens to hold `kind` here is a local, not an argument.
 * The `mult` by 0x994 is a real source-level multiply (mwcc could not
 * strength-reduce it); the `sll 5` beside it is the same expression pattern on
 * a power-of-two stride.
 *
 * `sltu $2,$0,$2 / xori $2,$2,1 / andi $6,$2,0xFF` is the recorded
 * bool-built-from-an-inequality-and-negated-in-one-expression idiom stored in a
 * `u8`; the second func_392B20 in the same arm passes the raw `s32` with no
 * mask, which is what proves the callee's parameter is NOT u8 and the mask
 * belongs to the local. */

typedef struct Ins {
    u8 pad000[0x87C];
    void *f87C;             /* +0x087C */
    u8 pad880[0x4FBC - 0x880];
    u8 f4FBC;               /* +0x4FBC */
    u8 pad4FBD[0x5DA0 - 0x4FBD];
    s32 f5DA0;              /* +0x5DA0 */
    s32 f5DA4;              /* +0x5DA4 */
    u8 pad5DA8[0x5EF1 - 0x5DA8];
    u8 f5EF1;               /* +0x5EF1 */
} Ins;

typedef struct Item { u8 pad00[0x6C]; s16 f6C; } Item;

extern const u8 D_00523ED0[];
extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d);
extern void insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *b, s32 *c);
extern void insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern s32  func_290460(void *h, s32 id);
extern void func_392B20(void *a, s32 b, s32 c);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32  insect_InsectTeamSlotPlaceOrderPop_514020(void *a);
extern void insect_InsectTeamSlotClearCell_5140b0(void *a, s32 b);
extern Item *insect_InsectTeamGetPiece_5138d0(void *a, s32 b);
extern void insect_InsectModelMemReleasePiece_512400(void *a, s16 b);
extern void insect_InsectPieceClearStatus_513340(Item *q, s32 k);
extern void insect_InsectBoardRemovePiece_4ef7f0(void *a, Item *q);

void insect_InsectBattleMenuLayoutConfirm_4ff040(Ins *o)
{
    s32 a1;
    s32 a2;
    s32 b1;
    s32 b2;
    void *p20;
    void *p19;
    void *p18;
    void *p17;
    void *p16;
    s32 kind;
    s32 n;
    Item *q;
    u8 flag;

    p20 = (u8 *)o + 0x4960;
    p19 = (u8 *)o + 0x4B4C;
    p18 = (u8 *)o + 0x5054;
    kind = o->f5EF1;
    /* ★★ THE LAST 9 WORDS WERE TWO SEPARATE LEVERS PULLED IN OPPOSITE
     * DIRECTIONS, and neither alone closes it:
     *   - the DEFINING-STATEMENT order sets the EMISSION order.  p17 has to be
     *     written first (mwcc still emits p16's `addiu` first, because the
     *     `mult` feeding p17 is issued early for its latency);
     *   - the DECLARATION order sets WHICH callee-saved register each gets.
     *     p17 has to be declared first to take $17.
     * With both in the "natural" p16-then-p17 order the unit is 9 words wrong
     * at the RIGHT length -- six in this arithmetic and three at case 0x1E's
     * uses.  Fixing only the statement order leaves 5; fixing only the
     * declaration order leaves the emission wrong.  ⇒ declaration order is a
     * real lever on this compiler once the statement order is already right,
     * which sharpens the "declaration order is 0 for 3" note the normal
     * sessions recorded. */
    p17 = (u8 *)o + kind * 0x994 + 0x35F8;
    p16 = (u8 *)o + kind * 0x20 + 0x4920;
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, (u8 *)o + 0x506C, 8);
        insect_InsectCursorSetGetCurCell_511a90((u8 *)o + 0x4F90, &a1, &a2);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523ED0, 1);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        o->f4FBC = o->f4FBC & 0xFD;
        break;
    case 0x1C:
        insect_InsectCursorSetGetCurCell_511a90((u8 *)o + 0x4F90, &b1, &b2);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523ED0, 0);
        flag = !(b1 != 0);
        func_392B20(p18, func_290460(o->f87C, 0xC37B), flag);
        func_392B20(p18, func_290460(o->f87C, 0xC37C), b1);
        break;
    case 0x1D:
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, 0xD, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0x1E:
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        n = insect_InsectTeamSlotPlaceOrderPop_514020(p16);
        insect_InsectTeamSlotClearCell_5140b0(p16, n);
        q = insect_InsectTeamGetPiece_5138d0(p17, n);
        if (q != 0) {
            insect_InsectModelMemReleasePiece_512400(p19, q->f6C);
            insect_InsectPieceClearStatus_513340(q, 0x21);
            insect_InsectBoardRemovePiece_4ef7f0(p20, q);
        }
        insect_InsectBattleSetState_50d8c0(o, 9, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    }
}
