/* rgp:protos */
#define RGP_SELF_WorldSubsysClear_3fd4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003fd4b0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    u8 pad008[0x8];
    s32 m10;         /* +0x10 */
    s32 m14;         /* +0x14 */
} Obj_FUN_003fd4b0;

void WorldSubsysClear_3fd4b0(Obj_FUN_003fd4b0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m10 = 0;
    o->m14 = 0;
}
