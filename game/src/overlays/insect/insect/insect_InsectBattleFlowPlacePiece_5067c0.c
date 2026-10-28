/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowPlacePiece_5067c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005067C0 -- 860 bytes, 215 instructions, 32 calls, 11 conditional
 * branches, br/ins 0.051.  A five-arm state dispatch of the
 * insect_InsectBattleGetStep_50d6a0(o, 0) family, from x_band.py's branch-light band.
 *
 * The compare CHAIN runs 0xB, 0x1C, 0x1B, 6, 1 -- REVERSED -- so source case
 * order is 1, 6, 0x1B, 0x1C, 0xB, and the three non-empty blocks are laid out
 * in that order (0x5068A4, 0x5068CC, 0x506920).
 *
 * Cases 6 and 0xB are EMPTY: 0xB (later in source) keeps the `beql` to the
 * epilogue head PLUS ONE (`ld $31` already ran in its slot) and 6 (earlier)
 * gets a plain `beq` + `nop`.
 *
 * The case-1 compare uses `$6` because case 1's body opens with
 * insect_InsectBattleSetState_50d8c0(o, 0xF, 1, -1) -- the dispatch constant is CSE'd into
 * the arm as its third argument.
 *
 * `o + 0x4960`, `o + 0x4B4C` and `o + (k << 5) + 0x4920` are all HOISTED into
 * $19/$17/$18 by the prologue, so all three are named locals; `o->f4F90` is
 * REMATERIALISED at each of its five sites and stays an array member written
 * inline.  insect-array-member-blocks-cse, both polarities in one function.
 *
 * STATEMENT order and DECLARATION order pull apart here exactly as
 * insect-stmt-order-vs-decl-order describes: retail EMITS `g` then `m` then
 * `p`, but parks them in $19, $17, $18 -- so `p` is DECLARED before `m` while
 * its statement comes after.
 *
 * The `+ 5` and `- 5` fixups both reload `o->f5EF1` rather than reusing `k`,
 * so the source tests the member and not the local.
 *
 * `(f32)sp74` is `lwc1` + `cvt.s.w` off the frame slot -- an s32 local
 * converted, not an f32 local.
 */

typedef struct Rec {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Rec;

typedef struct Ins {
    u8 pad0000[0x4F90];
    u8 f4F90[0x4FBC - 0x4F90];      /* +0x4F90 */
    u8 f4FBC;                       /* +0x4FBC */
    u8 pad4FBD[0x5EF1 - 0x4FBD];
    u8 f5EF1;                       /* +0x5EF1 */
} Ins;

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

void insect_InsectBattleFlowPlacePiece_5067c0(Ins *o)
{
    s32   sp7C;
    s32   sp78;
    s32   sp74;
    s32   sp70;
    f32   sp6C;
    f32   sp68;
    f32   sp64;
    u8   *g;
    u8   *p;
    u8   *m;
    Rec  *n;
    s32   k;
    s32   v;

    insect_InsectCursorSetGetCell_511a40(o->f4F90, 8, &sp7C, &sp78);
    insect_InsectCursorSetGetCell_511a40(o->f4F90, 9, &sp74, &sp70);
    k = o->f5EF1;
    g = (u8 *)o + 0x4960;
    m = (u8 *)o + 0x4B4C;
    p = (u8 *)o + (k << 5) + 0x4920;
    n = ((Rec *)insect_InsectTeamGetPiece_5138d0((u8 *)o + k * 0x994 + 0x35F8, sp78));
    if (o->f5EF1 == 0) {
        sp70 = sp70 + 5;
    }

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 0xF, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
        break;
    case 6:
        break;
    case 0x1B:
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 9, 0);
        o->f4FBC &= 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 0xC, 2, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x27);
        break;
    case 0x1C:
        if (n != 0) {
            insect_InsectBoardCellToWorld_4eda70(g, &sp6C, &sp68, &sp64, 1, (f32)sp74, (f32)sp70);
            insect_InsectPieceMoveTo_5157d0(n, 0, sp6C, sp68, sp64, 1.0f);
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                if (insect_InsectBoardGetPiece_4ee9a0(g, (s16)sp74, (s16)sp70) == 0) {
                    insect_InsectPieceSetStatus_5132d0(n, 0x21);
                    insect_InsectBoardPlacePiece_4ef830(g, n, (s16)sp74, (s16)sp70);
                    insect_InsectBoardCellToWorld_4eda70(g, &sp6C, &sp68, &sp64, 0,
                                        (f32)sp74, (f32)sp70);
                    insect_InsectPieceMoveTo_5157d0(n, 0, sp6C, sp68, sp64, 10.0f);
                    insect_InsectBattleSetState_50d8c0(o, 9, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                    insect_InsectPlaySe_510870(2);
                    v = sp70;
                    if (o->f5EF1 == 0) {
                        v = v - 5;
                    }
                    insect_InsectTeamSlotSetCell_5140c0(p, sp78, sp74, v);
                    insect_InsectTeamSlotPlaceOrderPush_514060(p, sp78);
                } else {
                    insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
                }
                return;
            } else {
                if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                    insect_InsectPieceClearStatus_513340(n, 0x21);
                    insect_InsectModelMemReleasePiece_512400(m, n->f6C);
                    insect_InsectBattleSetState_50d8c0(o, 9, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                    insect_InsectBattlePlaySe_4f45b0(o, 6);
                }
            }
        }
        break;
    case 0xB:
        break;
    }
}
