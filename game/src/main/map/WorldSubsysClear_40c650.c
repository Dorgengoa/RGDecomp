/* rgp:protos */
#define RGP_SELF_WorldSubsysClear_40c650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0040c650 {
    s32 m00;         /* +0x0 */
    u8 pad004[0x4];
    s32 m08;         /* +0x8 */
} Obj_FUN_0040c650;

void WorldSubsysClear_40c650(Obj_FUN_0040c650 *o)
{
    o->m00 = 0;
    o->m08 = 0;
}
