#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0026a1b0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
} Obj_FUN_0026a1b0;

void ScriptArgInitInt_26a1b0(Obj_FUN_0026a1b0 *o, s32 p0)
{
    o->m00 = 0;
    o->m04 = p0;
}
