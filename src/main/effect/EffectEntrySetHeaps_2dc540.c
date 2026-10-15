#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_002dc540 {
    u8 pad000[0xA4];
    s32 mA4;         /* +0xA4 */
    s32 mA8;         /* +0xA8 */
} Obj_FUN_002dc540;

void EffectEntrySetHeaps_2dc540(Obj_FUN_002dc540 *o, s32 p0, s32 p1)
{
    o->mA4 = p0;
    o->mA8 = p1;
}
