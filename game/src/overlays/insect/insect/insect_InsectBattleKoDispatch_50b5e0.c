/* rgp:protos */
#define RGP_SELF_insect_InsectBattleKoDispatch_50b5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050B5E0 -- 76 bytes, 19 instructions.  Both `beql`s jump INTO an
 * arm, which is the switch polarity; the compare chain runs 1 then 0, REVERSED
 * from the source case order 0, 1. */

/*rgp*/
/*rgp*/

void insect_InsectBattleKoDispatch_50b5e0(void *o)
{
    switch (insect_InsectBattleGetState_50d6f0(o, 5)) {
    case 0:
        break;
    case 1:
        insect_InsectBattleKoStep_4f99e0(o);
        break;
    }
}
