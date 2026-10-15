#include "types.h"
/* insect 0x004EF5E0 -- 144 bytes.  All three guards `goto` ONE cold
 * `return 0`, and that block is laid out BEFORE the body -- so it stands
 * before the body in the SOURCE too, with the body entered by its own
 * `goto ok`.  mwcc shortcuts the b arm's goto into a likely branch straight
 * to the epilogue by itself; spelling that arm `return 0` costs three words. */

extern void insect_InsectBoardCalcAttackRange_4ec720(void *o, void *e, void *q, s16 x, s16 y);
extern void insect_InsectBoardFindPiece_4ee190(void *w, void *e, s32 *x, s32 *y);
extern s32  insect_InsectBoardIsInAttackRange_4ee850(void *o, s32 x, s32 y);

s32 insect_InsectBoardAbilityInRange_4ef5e0(void *o, void *a, void *b, void *c, s32 x, s32 y)
{
    s32 gx;
    s32 gy;

    if (a == 0) {
        goto zero;
    }
    if (b == 0) {
        goto zero;
    }
    if (c != 0) {
        goto ok;
    }
zero:
    return 0;
ok:
    insect_InsectBoardCalcAttackRange_4ec720(o, c, a, (s16)x, (s16)y);
    insect_InsectBoardFindPiece_4ee190(o, b, &gx, &gy);
    return insect_InsectBoardIsInAttackRange_4ee850(o, gx, gy) != 0;
}
