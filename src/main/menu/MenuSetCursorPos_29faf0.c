#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0029faf0 {
    u8 pad000[0x5C];
    u8 m5C;         /* +0x5C */
    u8 m5D;         /* +0x5D */
} Obj_FUN_0029faf0;

void MenuSetCursorPos_29faf0(Obj_FUN_0029faf0 *o, u8 p0, u8 p1)
{
    o->m5C = p0;
    o->m5D = p1;
}
