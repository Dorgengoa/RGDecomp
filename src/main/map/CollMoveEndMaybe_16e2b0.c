#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0016e2b0 {
    u8 pad000[0x104];
    s32 m104;         /* +0x104 */
    u8 pad108[0x18];
    s32 m120;         /* +0x120 */
} Obj_FUN_0016e2b0;

void CollMoveEndMaybe_16e2b0(Obj_FUN_0016e2b0 *o)
{
    o->m104 = 0;
    o->m120 = 0;
}
