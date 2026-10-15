#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001f52b0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_001f52b0;

void IdBitmapReset_1f52b0(Obj_FUN_001f52b0 *o)
{
    o->m00 = 0;
    o->m02 = 0;
    o->m04 = 0;
    o->m08 = 0;
}
