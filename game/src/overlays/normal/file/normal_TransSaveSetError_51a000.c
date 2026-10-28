/* rgp:protos */
#define RGP_SELF_normal_TransSaveSetError_51a000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051A000 -- store then tail call.  The gp load of D_004847D0 sits
 * AFTER the `sh` in retail, which is the recorded "a gp load will not move
 * above a store" ordering: the store is written first in source. */

extern s16   D_004847FC;          /* gp - 0x974 */
extern void *D_004847D0;          /* gp - 0x9A0 */

/*rgp*/

void normal_TransSaveSetError_51a000(s32 a)
{
    D_004847FC = a;
    StateMachineSetState_28ede0(D_004847D0, 0xA, 0);
}
