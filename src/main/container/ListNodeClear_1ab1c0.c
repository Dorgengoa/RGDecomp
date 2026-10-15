#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001ab1c0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
} Obj_FUN_001ab1c0;

void ListNodeClear_1ab1c0(Obj_FUN_001ab1c0 *o)
{
    o->m08 = 0;
    o->m04 = 0;
    o->m00 = 0;
    o->m0C = 0;
}
