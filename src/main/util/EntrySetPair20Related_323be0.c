#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00323be0 {
    u8 pad000[0x20];
    s32 m20;         /* +0x20 */
    s32 m24;         /* +0x24 */
} Obj_FUN_00323be0;

void EntrySetPair20Related_323be0(Obj_FUN_00323be0 *o, s32 p0, s32 p1)
{
    o->m20 = p0;
    o->m24 = p1;
}
