#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0039dd10 {
    u8 pad000[0x28];
    s32 m28;         /* +0x28 */
    s32 m2C;         /* +0x2C */
} Obj_FUN_0039dd10;

void WarpMenuFadeReset_39dd10(Obj_FUN_0039dd10 *o)
{
    o->m28 = 0;
    o->m2C = 0;
}
