/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSaveState_50d650 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050d650 -- 68 B / 17 words (the three trailing nops in the listing are
 * link padding, not code).  Twin pair; only the two callees differ.
 * $17=o, $16=k; the scan's result goes straight through as argument two and
 * `k + 6` as argument three, with -1 in the jal delay slot as argument four.
 */

typedef struct Ins Ins;

/*rgp*/
/*rgp*/

void insect_InsectBattleSaveState_50d650(Ins *o, s32 k)
{
    insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetState_50d6f0(o, k), k + 6, -1);
}
