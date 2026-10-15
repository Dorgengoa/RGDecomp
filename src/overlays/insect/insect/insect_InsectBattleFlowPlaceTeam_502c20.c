#include "types.h"
/* insect 0x00502C20 -- 732 bytes, 183 instructions, 26 calls, 6 conditional
 * branches.  Third unit of the JUMP-TABLE class.
 *
 * ★ CASE ORDER OFF THE TABLE.  jtbl_00524E50 has EIGHT entries and indices
 * 0, 6 and 7 all point at the shared join 0x00502ED0 -- so those three cases
 * are present in the source with empty bodies, and it is their presence that
 * makes the case set DENSE enough for mwcc to emit a table at all.  Written
 * with only the five real cases mwcc compiles a compare CHAIN instead (that is
 * measured -- see insect_InsectBattleFlowSelectVictoryCond_502a30, where the same omission cost 3 words
 * and a completely different dispatch).
 *
 * The gp global at `-0x1D0($28)` is 0x00484FA0.  `_gp` is 0x00485170 so the
 * window is 0x47D170..0x48D170 and this address is INSIDE it -- it must stay a
 * PLAIN (non-`const`) extern, unlike every `D_0052xxxx`.
 *
 * Case 2's guard is the [[at-compare-class]] shape read the easy way round:
 * `slti $2,$2,0x5` lands in a GPR and feeds a `bnel`, so the branch is taken
 * on a strict `<` and the source's own operator is the natural `>= 5` with the
 * SHORT arm as the fall-through.  (Had retail put it in `$1` the source would
 * have had to be spelled `> 4`.)
 *
 * Both stack pairs are `s32`.  `sp74`/`sp70` are read three ways -- `lw` for
 * the +5 update, `lh` for the two `s16` parameters of insect_InsectBoardPlacePiece_4ef830, and
 * `lwc1`+`cvt.s.w` for the float conversion.  Declaring them `s16` would make
 * the float path `lh`+`mtc1`+`cvt.s.w`, one instruction long at each site.
 */

typedef struct Ins {
    u8  pad000[0x4F90];
    u8  f4F90[0x2C];            /* +0x4F90 -- sub-object, passed by address */
    u8  f4FBC;                  /* +0x4FBC */
    u8  pad4FBD[0x5EF1 - 0x4FBD];
    u8  f5EF1;                  /* +0x5EF1 */
} Ins;

extern s32 D_00484FA0;          /* gp-window: PLAIN, never const */

extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleNextStep_50d740(Ins *o, s32 a);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleMemberListGrey_4fae30(Ins *o, void *p);
extern void insect_InsectPlaySe_510870(s32 a);
extern void insect_InsectCursorSetPushPage_511cf0(void *g, s32 a, s32 b);
extern void insect_InsectCursorSetPageSetCell_511c20(void *g, s32 a, s32 b, s32 c);
extern s32  insect_InsectCursorSetFindPage_511e60(void *g, s32 a);
extern void insect_InsectCursorSetGetCell_511a40(void *g, s32 a, s32 *b, s32 *c);
extern void insect_InsectTeamSlotGetCell_513d90(void *p, s32 a, s32 *b, s32 *c, s32 d);
extern void *insect_InsectTeamGetPiece_5138d0(void *p, s32 a);
extern void insect_InsectPieceSetStatus_5132d0(void *q, s32 a);
extern void insect_InsectTeamSlotPlaceOrderPush_514060(void *p, s32 a);
extern void insect_InsectBoardPlacePiece_4ef830(void *p, void *q, s16 x, s16 y);
extern void insect_InsectBoardCellToWorld_4eda70(void *p, f32 *a, f32 *b, f32 *c, s32 d, f32 x, f32 y);
extern void insect_InsectPieceMoveTo_5157d0(void *q, s32 a, f32 x, f32 y, f32 z, f32 w);

void insect_InsectBattleFlowPlaceTeam_502c20(Ins *o)
{
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    void *t4920;
    void *t35F8;
    void *t4960;
    void *q;
    s32 k;

    t4960 = (u8 *)o + 0x4960;
    k = o->f5EF1;
    t4920 = (u8 *)o + k * 0x20 + 0x4920;
    t35F8 = (u8 *)o + k * 0x994 + 0x35F8;

    if (insect_InsectBattleGetStep_50d6a0(o, 0) == 0x1B) {
        insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
    }

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 0:
        break;
    case 1:
        D_00484FA0 = 0;
        insect_InsectBattleNextStep_50d740(o, 0);
        break;
    case 2:
        if (D_00484FA0 >= 5) {
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        } else {
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0xF, 1, -1);
            insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 8), 0,
                                D_00484FA0);
            insect_InsectTeamSlotGetCell_513d90(t4920, D_00484FA0, &sp7C, &sp78, -1);
            insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 9),
                                sp7C, sp78);
        }
        break;
    case 3:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) {
            insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        }
        break;
    case 4:
        q = insect_InsectTeamGetPiece_5138d0(t35F8, D_00484FA0);
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 9, &sp74, &sp70);
        if (q != 0) {
            if (o->f5EF1 == 0) {
                sp70 = sp70 + 5;
            }
            insect_InsectPieceSetStatus_5132d0(q, 0x21);
            insect_InsectBoardPlacePiece_4ef830(t4960, q, (s16)sp74, (s16)sp70);
            insect_InsectBoardCellToWorld_4eda70(t4960, &sp6C, &sp68, &sp64, 0,
                                (f32)sp74, (f32)sp70);
            insect_InsectPieceMoveTo_5157d0(q, 0, sp6C, sp68, sp64, 10.0f);
            insect_InsectPlaySe_510870(2);
            insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
            insect_InsectTeamSlotPlaceOrderPush_514060(t4920, D_00484FA0);
            D_00484FA0 = D_00484FA0 + 1;
        }
        break;
    case 5:
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        o->f4FBC = o->f4FBC | 2;
        insect_InsectBattleSetState_50d8c0(o, 0xB, 0, -1);
        break;
    case 6:
        break;
    case 7:
        break;
    }
    insect_InsectBattleMemberListGrey_4fae30(o, t35F8);
}
