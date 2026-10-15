#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00178470 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
    u8 pad014[0x8];
    s32 m1C;         /* +0x1C */
    u8 pad020[0x4];
    s32 m24;         /* +0x24 */
} Obj_FUN_00178470;

void ScreenFadeBlockReset_178470(Obj_FUN_00178470 *o)
{
    o->m10 = 0;
    o->m0C = 0;
    o->m24 = 0;
    o->m1C = 0;
}
