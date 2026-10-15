#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001f57c0 {
    u8 pad000[0x8];
    s32 m08;         /* +0x8 */
    s16 m0C;         /* +0xC */
} Obj_FUN_001f57c0;

void TaskEntryReset_1f57c0(Obj_FUN_001f57c0 *o)
{
    o->m0C = 0;
    o->m08 = 0;
}
