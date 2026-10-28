/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecMove_51b2f0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0051B2F0 -- 656 bytes, 164 instructions.
 *
 * Interpolates between the two anchor points of a link and pushes the result
 * through insect_InsectBoardCellToWorld_4eda70 / insect_InsectPieceMoveTo_5157d0, the same pair
 * insect_InsectBattleFlowPlaceTeam_502c20 and insect_InsectBattleFlowPlacePiece_5067c0 already carry.
 *
 * The two `bnez $2 / div / break 0,7` triples are mwcc's divide trap, which
 * only appears with `#pragma divbyzerocheck on`
 * (levers.d/mwcc-divbyzerocheck-pragma).
 *
 * Both dispatches branch INTO their arms with a `beql`, so both are real
 * `switch`es and the source case order is the compare chain REVERSED.
 */

typedef struct Arg {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
    u8  pad08[0xC - 0x8];
    f32 fC;                         /* +0x0C */
    s32 f10;                        /* +0x10 */
} Arg;

/*rgp*/
extern s32   abs(s32 v);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

s32 insect_InsectSeqExecMove_51b2f0(Arg *arg)
{
    s32   sp8C;
    s32   sp88;
    s32   sp84;
    s32   sp80;
    f32   sp70[3];
    void *h;
    void *a;
    void *b;
    s32   dx;
    s32   dy;
    f32   px;
    f32   py;
    f32   t;
    f32   u;
    f32   fx;
    f32   fy;
    f32   cx;
    f32   cy;

    h = InsectBattleGet_31a8d0();
    if ((arg == 0) || (h == 0)) {
        return 1;
    }
    a = insect_InsectBattleGetActorSlot_50db40(h, 0);
    b = insect_InsectBattleGetActorSlot_50db40(h, 1);
    h = (u8 *)h + 0x4960;
    if ((a == 0) || (b == 0)) {
        return 1;
    }
    t = arg->fC;
    insect_InsectBoardFindPiece_4ee190(h, a, &sp8C, &sp88);
    insect_InsectBoardFindPiece_4ee190(h, b, &sp84, &sp80);
    switch (arg->f4) {
    case 0:
        insect_InsectPieceSavePos_5159f0(a);
        switch (arg->f10) {
        case 0:
            cx = (f32)(sp84 - sp8C);
            cy = (f32)(sp80 - sp88);
            fx = cx * t;
            fy = cy * t;
            px = fx + (f32)sp8C;
            py = fy + (f32)sp88;
            break;
        case 1:
            cx = (f32)(sp84 - sp8C);
            cy = (f32)(sp80 - sp88);
            u = 1.0f - t;
            fx = cx * u;
            fy = cy * u;
            dx = sp8C - sp84;
            dy = sp88 - sp80;
            if (dx != 0) {
                dx = dx / abs(dx);
            }
            if (dy != 0) {
                dy = dy / abs(dy);
            }
            px = (f32)dx + (fx + (f32)sp84);
            py = (f32)dy + (fy + (f32)sp80);
            break;
        }
        insect_InsectBoardCellToWorld_4eda70(h, &sp70[0], &sp70[1], &sp70[2], 0, px, py);
        insect_InsectPieceMoveTo_5157d0(a, 0, sp70[0], sp70[1], sp70[2], 10.0f);
        arg->f4 = arg->f4 + 1;
        break;
    case 1:
        if (insect_InsectPieceIsMoveDone_514a20(a) == 0) {
            break;
        }
        return 1;
    }
    return 0;
}
