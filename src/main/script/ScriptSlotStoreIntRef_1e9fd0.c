#include "types.h"

/* Only in state 3, forward the value into the sub-object.
   Proven at ScriptSlotStoreFloatRef_1e9fb0. */

typedef struct Sub_FUN_001e9fd0 {
    u8 pad000[0x4];
    s32 f;          /* +0x4 */
} Sub_FUN_001e9fd0;

typedef struct Obj_FUN_001e9fd0 {
    s32 g;             /* +0x0 */
    Sub_FUN_001e9fd0 *p;   /* +0x4 */
} Obj_FUN_001e9fd0;

void ScriptSlotStoreIntRef_1e9fd0(Obj_FUN_001e9fd0 *o, s32 value)
{
    if (o->g == 3) {
        o->p->f = value;
    }
}
