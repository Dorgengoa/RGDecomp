#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00176ae0 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_00176ae0;

void ScriptVmSetCmdTable_176ae0(Obj_FUN_00176ae0 *o, s32 p0, s32 p1)
{
    o->m08 = p0;
    o->m04 = p1;
}
