#include "types.h"
/* insect 0x00505B60 -- 888 bytes, 222 instructions, 30 calls, 10 conditional
 * branches.  A six-state dispatch over jtbl_00524EA0 (7 entries; index 0 points
 * at the shared exit 0x00505EBC, so case 0 is present with an empty body --
 * [[insect-jump-table-density]]).  Blocks are in ascending case order.
 *
 * Case 4's inner dispatch is a switch, not a chain: the converted beql at
 * 0x00505D70 carries CASE 1'S OWN daddu $4,$18,$0, while the PLAIN beq above it
 * carries v = 5, a statement that runs on both edges.  Compare chain 2 then 1
 * is REVERSED, so source order is 1 then 2.
 *
 * sel is initialised to -1 BEFORE insect_InsectCursorSetGetEvents_5119f0 and passed as its second
 * argument, so retail materialises the constant once and shares $17 between the
 * local and the literal.  Write both plainly and let mwcc share it -- an
 * argument never materialised in its own block is not a missing instruction.
 *
 * k = 5 and v = 5 both sit in a PLAIN branch's delay slot, which is the tell
 * that they are statements ahead of the guard rather than assignments inside an
 * arm: a plain branch's slot runs on both edges.
 *
 * c.lt.s $f0,$f1 against 1.0f with bc1t branching AWAY is >= 1.0f.  The nop
 * between the mtc1 and the compare is an FPU hazard, compiler output.
 *
 * sltu $2,$0,$2 / xori $2,$2,1 / andi $6,$2,0xFF is the recorded
 * bool-built-from-an-inequality-and-negated-in-one-expression stored in a u8;
 * the SECOND func_392B20 passes the same stack value raw with no mask, which is
 * what proves the callee's parameter is s32 and the mask belongs to the local.
 *
 * $16 carries two disjoint source variables -- k in case 4 and the loop counter
 * in case 6.  They are separate locals.
 */

typedef struct Ins {
    u8  pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8  pad880[0x35F8 - 0x880];
    u8  f35F8[0x4F90 - 0x35F8];
    u8  f4F90[0x2C];            /* +0x4F90 */
    u8  f4FBC;                  /* +0x4FBC */
    u8  pad4FBD[0x5054 - 0x4FBD];
    u8  f5054[0x18];            /* +0x5054 */
    u8  f506C[0x5DA0 - 0x506C];
    s32 f5DA0;                  /* +0x5DA0 */
    s32 f5DA4;                  /* +0x5DA4 */
} Ins;

extern const u8 D_00523C10[];

extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern void insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d);
extern void insect_InsectCursorSetPushPage_511cf0(void *g, s32 a, s32 b);
extern void insect_InsectCursorSetGetCurCell_511a90(void *g, s32 *a, s32 *b);
extern s32  insect_InsectCursorSetGetEvents_5119f0(void *g, s32 m);
extern void insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern void *insect_InsectTeamGetPiece_5138d0(void *p, s32 i);
extern void insect_InsectPieceClearStatus_513340(void *q, s32 k);

extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32   func_290770(void *h, s32 id);
extern void  func_2907A0(void *h, s32 id, f32 a);
extern s32   func_290460(void *h, s32 id);
extern void  func_392B20(void *a, s32 b, s32 c);

void insect_InsectBattleFlowManualControlConfirm_505b60(Ins *o)
{
    s32 sp5C;
    s32 sp58;
    s32 i;
    s32 sel;
    s32 k;
    s32 m;
    u8 flag;
    void *q;
    s32 v;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 0:
        break;
    case 1:
        insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, o->f506C, 0x2E);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
        break;
    case 2:
        if (func_290770(o->f87C, 0xC378) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
        }
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523C10, 1);
        break;
    case 3:
        insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        o->f4FBC = o->f4FBC & 0xFD;
        break;
    case 4:
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &sp5C, &sp58);
        flag = !(sp5C != 0);
        func_392B20(o->f5054, func_290460(o->f87C, 0xC37B), flag);
        func_392B20(o->f5054, func_290460(o->f87C, 0xC37C), sp5C);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523C10, 0);
        sel = -1;
        m = insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1);
        k = 5;
        if ((m & 0x80) != 0) {
            sel = sp5C;
        }
        if ((m & 0x20) != 0) {
            if (sel == -1) {
                sel = 2;
                k = 6;
            }
        }
        if (sel != -1) {
            v = 5;
            switch (sel) {
            case 1:
                insect_InsectBattleSetFlag_50dad0(o, 0xE);
                break;
            case 2:
                v = 6;
                break;
            }
            insect_InsectBattleSetStep_50d7a0(o, v, 0, -1);
            insect_InsectBattlePlaySe_4f45b0(o, k);
        }
        break;
    case 5:
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, 0xF, 0, -1);
        break;
    case 6:
        func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, 0xE, 0, -1);
        insect_InsectBattleClearFlag_50da90(o, 0x29);
        func_2907A0(o->f878, 0x7546, 0.0f);
        i = 0;
        do {
            q = insect_InsectTeamGetPiece_5138d0(o->f35F8, i);
            if (q != 0) {
                insect_InsectPieceClearStatus_513340(q, 0x1A);
            }
            i = i + 1;
        } while (i < 5);
        break;
    }
}
