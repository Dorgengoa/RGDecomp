/* rgp:protos */
#define RGP_SELF_PartyResetSpotTimeAndDistMaybe_3c96b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003c96b0 {
    u8 pad000[0x118];
    s64 m118;         /* +0x118 */
    s32 m120;         /* +0x120 */
} Obj_FUN_003c96b0;

void PartyResetSpotTimeAndDistMaybe_3c96b0(Obj_FUN_003c96b0 *o)
{
    o->m118 = 0;
    o->m120 = 0;
}
