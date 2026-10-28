/* rgp:protos */
#define RGP_SELF_PadKeyCapReset_1837f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001837f0 {
    u8 pad000[0x25C];
    s32 m25C;         /* +0x25C */
    s32 m260;         /* +0x260 */
} Obj_FUN_001837f0;

void PadKeyCapReset_1837f0(Obj_FUN_001837f0 *o)
{
    o->m25C = 0;
    o->m260 = 0;
}
