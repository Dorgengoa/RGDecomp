#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0041e7a0 {
    s32 m00;         /* +0x0 */
    u8 pad004[0x4];
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
} Obj_FUN_0041e7a0;

void WorldSubsysClear_41e7a0(Obj_FUN_0041e7a0 *o)
{
    o->m00 = 0;
    o->m08 = 0;
    o->m0C = 0;
}
