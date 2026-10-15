#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00304a00 {
    u8 pad000[0x1E];
    s16 m1E;         /* +0x1E */
    s16 m20;         /* +0x20 */
    s16 m22;         /* +0x22 */
} Obj_FUN_00304a00;

void DoorCursorResetState_304a00(Obj_FUN_00304a00 *o)
{
    o->m1E = 0;
    o->m20 = 0;
    o->m22 = 0;
}
