#include "types.h"

/* Only in state 3, forward the value into the sub-object.
   Proven at ScriptSlotStoreFloatRef_1e9fb0. */

typedef struct Sub_FUN_00249010 {
    u8 pad000[0x4];
    f32 f;          /* +0x4 */
} Sub_FUN_00249010;

typedef struct Obj_FUN_00249010 {
    s32 g;             /* +0x0 */
    Sub_FUN_00249010 *p;   /* +0x4 */
} Obj_FUN_00249010;

void ScriptSetRefFloat_249010(Obj_FUN_00249010 *o, f32 value)
{
    if (o->g == 3) {
        o->p->f = value;
    }
}
