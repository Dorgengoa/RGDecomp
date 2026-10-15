#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001efa20 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
} Obj_FUN_001efa20;

void ListNodeInit_1efa20(Obj_FUN_001efa20 *o)
{
    o->m00 = 0;
    o->m04 = 0;
}
