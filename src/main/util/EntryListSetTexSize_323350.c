#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00323350 {
    u8 pad000[0x20];
    s16 m20;         /* +0x20 */
    s16 m22;         /* +0x22 */
} Obj_FUN_00323350;

void EntryListSetTexSize_323350(Obj_FUN_00323350 *o, s16 p0, s16 p1)
{
    o->m20 = p0;
    o->m22 = p1;
}
