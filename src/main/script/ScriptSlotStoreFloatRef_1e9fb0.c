#include "types.h"

/* Only in state 3, forward the float into the sub-object. */

typedef struct Sub_FUN_001e9fb0 {
    u8 pad000[0x4];
    f32 m4;            /* +0x04 */
} Sub_FUN_001e9fb0;

typedef struct Obj_FUN_001e9fb0 {
    s32 state;         /* +0x00 */
    Sub_FUN_001e9fb0 *p;   /* +0x04 */
} Obj_FUN_001e9fb0;

void ScriptSlotStoreFloatRef_1e9fb0(Obj_FUN_001e9fb0 *o, f32 value)
{
    if (o->state == 3) {
        o->p->m4 = value;
    }
}
