/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetSoundBank_50db50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x50DB50 -- 8 B / 2 words.  `jr $31 / lw $2, 0x35F0($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x35F0];
    s32 m35F0;                 /* +0x35F0 */
} Obj;

s32 insect_InsectBattleGetSoundBank_50db50(Obj *o)
{
    return o->m35F0;
}
