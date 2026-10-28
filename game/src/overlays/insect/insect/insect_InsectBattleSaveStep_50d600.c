/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSaveStep_50d600 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050d600 -- 68 B / 17 words (the three trailing nops in the listing are
 * link padding, not code).  Twin pair; only the two callees differ.
 * $17=o, $16=k; the scan's result goes straight through as argument two and
 * `k + 6` as argument three, with -1 in the jal delay slot as argument four.
 */

typedef struct Ins Ins;

/*rgp*/
/*rgp*/

void insect_InsectBattleSaveStep_50d600(Ins *o, s32 k)
{
    insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, k), k + 6, -1);
}
