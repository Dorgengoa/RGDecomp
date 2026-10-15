#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001645b0 {
    u8 pad000[0xF0];
    s32 mF0;         /* +0xF0 */
    s32 mF4;         /* +0xF4 */
} Obj_FUN_001645b0;

void PrimBatchSetBuffer_1645b0(Obj_FUN_001645b0 *o, s32 p0)
{
    o->mF0 = p0;
    o->mF4 = p0;
}
