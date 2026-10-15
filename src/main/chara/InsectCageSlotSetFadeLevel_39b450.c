#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0039b450 {
    u8 pad000[0x24];
    f32 m24;         /* +0x24 */
    s32 m28;         /* +0x28 */
} Obj_FUN_0039b450;

void InsectCageSlotSetFadeLevel_39b450(Obj_FUN_0039b450 *o, f32 f0)
{
    o->m24 = f0;
    o->m28 = 0;
}
