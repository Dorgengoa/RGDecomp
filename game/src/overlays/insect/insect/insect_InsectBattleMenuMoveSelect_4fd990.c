/* rgp:protos */
#define RGP_SELF_insect_InsectBattleMenuMoveSelect_4fd990 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004FD990 -- 200 bytes, 50 instructions, 9 calls, 2 conditional
 * branches, br/ins 0.040.  A two-arm `insect_InsectBattleGetStep_50d6a0(o, 2)` state
 * dispatch from x_band.py's branch-light band.
 *
 * Both tests are `beql $2, $3, <block>` -- branches INTO the arm with its
 * first argument load in the delay slot -- so this is a real `switch` and the
 * compare chain 0x1D, 1 is REVERSED from the source order 1, 0x1D.  The block
 * ADDRESSES agree with the source order and not with the chain.
 */

typedef struct Ins Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleMenuMoveSelect_4fd990(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectBattleSetFlag_50dad0(o, 0x20);
        insect_InsectBattleSetFlag_50dad0(o, 0x21);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        return;
    case 0x1D:
        insect_InsectBattleClearFlag_50da90(o, 0x20);
        insect_InsectBattleClearFlag_50da90(o, 0x21);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1D, 0, -1);
        return;
    }
}
