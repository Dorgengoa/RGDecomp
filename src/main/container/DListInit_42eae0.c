#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0042eae0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s16 m08;         /* +0x8 */
    s16 m0A;         /* +0xA */
} Obj_FUN_0042eae0;

void DListInit_42eae0(Obj_FUN_0042eae0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    o->m0A = 0;
}
