/* rgp:protos */
#define RGP_SELF_insect_InsectBoardCanMoveAndHit_4ec4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EC4A0 -- 212 bytes, 53 instructions, 6 calls, 2 conditional
 * branches, br/ins 0.038.  From x_band.py's branch-light band.
 *
 * The FIRST insect_InsectBoardFindPiece_4ee190 call sets only $6 and $7: $4 and $5 still hold
 * the incoming arguments, so its first two arguments are the parameters passed
 * straight through.  m2c renders that call with two arguments because it only
 * sees the registers the function TOUCHES -- the pass-through-argument trap
 * overlay-c-pipeline records.
 *
 * `dsll32 $6, $17, 16 / dsra32 $6, $6, 16` is a 16-bit sign extension of a
 * value already in a register, i.e. an explicit `(s16)` cast at the call site
 * (normal-s16-cast-sign-extension), not a narrow parameter: the same two
 * values are handed to insect_InsectBoardIsMovable_4ee930 with a bare `daddu`.
 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBoardCanMoveAndHit_4ec4a0(void *o, s32 k, void *m, s64 x, s64 y)
{
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    insect_InsectBoardFindPiece_4ee190(o, (void *)k, &a, &b);
    insect_InsectBoardFindPiece_4ee190(o, m, &c, &d);
    insect_InsectBoardCalcMoveRange_4ed180(o, k);
    if (insect_InsectBoardIsMovable_4ee930(o, x, y) != 0) {
        insect_InsectBoardMarkAdjacentTargets_4ecf80(o, k, (short)((s16)x), (short)((s16)y));
        if (insect_InsectBoardIsTargetMarked_4ee8c0(o, c, d) != 0) {
            return 1;
        }
    }
    return 0;
}
