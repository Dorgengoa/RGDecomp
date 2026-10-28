/* rgp:protos */
#define RGP_SELF_ScriptVmReset_176bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00176bd0 {
    u8 pad000[0x3C];
    s32 m3C;         /* +0x3C */
    s32 m40;         /* +0x40 */
    s32 m44;         /* +0x44 */
} Obj_FUN_00176bd0;

void ScriptVmReset_176bd0(Obj_FUN_00176bd0 *o)
{
    o->m3C = 0;
    o->m40 = 0;
    o->m44 = 0;
}
