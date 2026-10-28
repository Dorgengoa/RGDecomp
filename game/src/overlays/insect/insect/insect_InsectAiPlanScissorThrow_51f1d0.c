/* rgp:protos */
#define RGP_SELF_insect_InsectAiPlanScissorThrow_51f1d0 1
#include "port/game_protos.h"
#line 1
/* MATCH: 201 words / 804 bytes.
 * Keep the initial x coordinate separate and restore it on the loop backedge.
 * This gives nx its scalar stack home without a redundant pre-guard reload.
 * Verified with mwccps2 3.0.1b210, standard -O4 flags.
 */
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0051F1D0 -- 804 bytes, 201 instructions, 14 calls, 22 branches,
 * one 17-entry jump table (insect_jtbl_00525640, 16 of whose arms are the same
 * target) and TWO divide-by-zero traps -- so this unit is in the
 * `#pragma divbyzerocheck on` cohort.
 */

typedef struct A {
    u8   pad00[0x58];
    void *f58;                      /* +0x58 */
    void *f5C;                      /* +0x5C */
    u8   pad60[0x94 - 0x60];
    void *f94;                      /* +0x94 */
} A;

typedef struct B {
    u8   pad00[0x18];
    s8   f18;                       /* +0x18 */
    u8   pad19[0x38 - 0x19];
    s8   f38;                       /* +0x38 */
    s8   f39;                       /* +0x39 */
} B;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32  abs(s32 v);

s32 insect_InsectAiPlanScissorThrow_51f1d0(A *a, B *b)
{
    s32 ox;
    s32 oy;
    s32 sx;
    s32 cc;
    s32 nx;
    s32 initial_nx;
    s32 n;
    void *h;
    s32 sy;
    s32 r;
    s32 dy;
    s32 dx;
    s32 y;
    s32 x;
    s32 ty;
    s32 tx;
    s32 ny;

    if (b == 0) {
        return 0;
    }

    insect_InsectAbilityTableFilter_51d020(a->f5C, b->f38, b->f39, b->f18, &a->f94);
    h = a->f94;
    if (h == 0) {
        return 0;
    }

    insect_InsectBoardFindPiece_4ee190(a->f58, b, &ox, &oy);
    insect_InsectBoardCalcMoveRange_4ed180(a->f58, b);

    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardIsMovable_4ee930(a->f58, (long long)(x), (long long)(y)) == 0) {
                continue;
            }
            insect_InsectBoardCalcAttackRange_4ec720(a->f58, h, b, x, y);

            for (ty = 0; ty < 7; ty++) {
                for (tx = 0; tx < 5; tx++) {
                    if (insect_InsectBoardIsInAttackRange_4ee850(a->f58, tx, ty) == 0) {
                        continue;
                    }
                    cc = insect_InsectBoardGetPiece_4ee9a0(a->f58, tx, ty);
                    switch (b->f38) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        break;
                    case 4:
                        if (cc == 0) {
                            break;
                        }
                        dx = abs(ox - tx);
                        dy = abs(oy - ty);
                        if (dx != 0) {
                            sx = (ox - tx) / dx;
                        }
                        if (dy != 0) {
                            sy = (oy - ty) / dy;
                        }
                        initial_nx = sx + ox;
                        nx = initial_nx;
                        ny = sy + oy;
                        if (nx >= 0 && nx < 5 && ny >= 0 && ny < 7) {
                            if (insect_InsectBoardIsHole_4ee7e0(a->f58, nx, ny) != 0) {
                                insect_InsectAiAddMoveSpecialAction_51f050(a, b, cc, h, sx, sy, tx, ty);
                            } else {
                                n = 0;
                                do {
                                    r = insect_InsectBoardGetPiece_4ee9a0(a->f58, nx, ny);
                                    if (r != 0) {
                                        nx = initial_nx;
                                        n++;
                                        ny = ny + sy;
                                    }
                                } while (r != 0);
                                if (n != 0) {
                                    insect_InsectAiAddMoveSpecialAction_51f050(a, b, cc, h, sx, sy, tx, ty);
                                }
                            }
                        } else {
                            insect_InsectAiAddMoveSpecialAction_51f050(a, b, cc, h, sx, sy, tx, ty);
                        }
                        break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                        break;
                    }
                }
            }
        }
    }
    return 1;
}
