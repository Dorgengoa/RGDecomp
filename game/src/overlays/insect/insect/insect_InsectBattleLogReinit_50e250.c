/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLogReinit_50e250 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E250 -- pass-28 unnamed-listing conversion.  A two-argument
 * tail call built entirely out of the one incoming pointer; the leading
 * `daddu $2, $4, $0` is the copy mwcc needs because $4 is overwritten by the
 * first of the two addresses. */
typedef struct Big {
    u8 pad0000[0x6B8];
    u8 m6B8[0x5080 - 0x6B8];   /* +0x06B8 */
    u8 m5080[4];               /* +0x5080 */
} Big;

/*rgp*/

void insect_InsectBattleLogReinit_50e250(Big *o)
{
    insect_InsectBattleLogAllocLines_51c540(o->m5080, o->m6B8);
}
