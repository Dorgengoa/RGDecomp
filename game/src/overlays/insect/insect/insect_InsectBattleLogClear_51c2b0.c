/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogClear_51c2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051C2B0 -- 64 bytes, 16 instructions. */

/*rgp*/
/*rgp*/

void insect_InsectBattleLogClear_51c2b0(void *a)
{
    do {
        insect_InsectBattleLogScrollUp_51c180(a);
    } while (!((unsigned char)insect_InsectBattleLogIsEmpty_51b8b0(a)));
}
