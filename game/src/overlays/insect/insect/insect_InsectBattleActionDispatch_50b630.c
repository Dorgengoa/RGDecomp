/* rgp:protos */
#define RGP_SELF_insect_InsectBattleActionDispatch_50b630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050B630 -- 132 bytes, 33 instructions.
 *
 * A four-arm switch: the compare chain is 3,2,1,0 while the arm bodies are
 * laid out 1,2,3 -- the compare chain REVERSED from source case order.
 * case 0 is a real, empty arm: it gets its own beql to the epilogue.
 */

typedef struct Obj Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleActionDispatch_50b630(Obj *o)
{
    switch (insect_InsectBattleGetState_50d6f0(o, 3)) {
    case 0:
        break;
    case 1:
        insect_InsectBattleMoveSeqStep_4fa680(o);
        break;
    case 2:
        insect_InsectBattleAttackSeqStep_4fa210(o);
        break;
    case 3:
        insect_InsectBattleSpecialSeqStep_4f9d90(o);
        break;
    }
}
