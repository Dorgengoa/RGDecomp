/* rgp:protos */
#define RGP_SELF_insect_InsectTeamSlotPlaceOrderPush_514060 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514060 -- 17 instructions.  The slot address is materialised
 * once (`addiu $7, $3, 0xF`) and used for both the compare and the store, so
 * the source names the pointer.  MEASURED: the pointer must be spelled
 * `base + i + 15` -- left-associative, so `base + i` is formed first and the
 * +15 becomes a second `addiu`.  `&base[i + 15]` folds the index instead and
 * costs 3 words; `&base[i]` with `p[15]` folds the other way and is one word
 * SHORT.  The parameter is s32, not s8: an s8 `v` adds a dsll32/dsra32 pair.
 */

void insect_InsectTeamSlotPlaceOrderPush_514060(s8 *base, s32 v)
{
    s32 i;
    s8 *p;

    for (i = 0; i < 5; i++) {
        p = base + i + 15;
        if (*p == -1) {
            *p = v;
            return;
        }
        if (*p == v) {
            return;
        }
    }
}
