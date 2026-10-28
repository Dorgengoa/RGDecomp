/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowLoad_50a140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050A140 -- 160 bytes, 40 instructions.  Both `beql`s jump INTO
 * their arm, so this is a switch; the compare chain runs 0xA then 1, REVERSED
 * from the source case order 1 then 0xA, and the arms are laid out in source
 * order. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowLoad_50a140(void *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 1, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 10, 0, -1);
        break;
    case 10:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0) {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
            insect_InsectBattleNextState_50d750(o, 0);
        }
        break;
    }
}
