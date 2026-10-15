#include "types.h"

/* Return val only while gate is clear.  Spelled != 0 so the beql
   makes the VALUE the branch target and the 0 the fall-through --
   the branch-layout rule, proven at PadGetHeldMask_183d30. */

typedef struct Obj_FUN_001c2bb0 {
    s32 gate;         /* +0x0 */
    s32 val;         /* +0x4 */
} Obj_FUN_001c2bb0;

s32 ScriptArgGetStr_1c2bb0(Obj_FUN_001c2bb0 *o)
{
    if (o->gate != 0) {
        return 0;
    }
    return o->val;
}
