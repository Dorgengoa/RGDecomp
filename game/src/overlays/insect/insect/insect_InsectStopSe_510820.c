/* rgp:protos */
#define RGP_SELF_insect_InsectStopSe_510820 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510820 -- 18 instructions.  The call result lands straight in $4
 * and is tested there, so it is the first argument of the inner call. */

/*rgp*/
/*rgp*/

void insect_InsectStopSe_510820(s32 id)
{
    void *h;

    if (id != -1) {
        h = GetCurrentScene_1f5be0();
        if (h != 0) {
            GameSceneSoundSlot5StopSe_1d0590(h, id);
        }
    }
}
