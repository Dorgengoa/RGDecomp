/* rgp:protos */
#define RGP_SELF_WorldSubsysClear_428650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00428650 {
    s32 m00;         /* +0x0 */
    u8 pad004[0x4];
    s32 m08;         /* +0x8 */
} Obj_FUN_00428650;

void WorldSubsysClear_428650(Obj_FUN_00428650 *o)
{
    o->m00 = 0;
    o->m08 = 0;
}
