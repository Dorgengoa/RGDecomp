/* rgp:protos */
#define RGP_SELF_ScriptSlotStoreFloatRef_2cc8e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Only in state 3, forward the value into the sub-object.
   Proven at ScriptSlotStoreFloatRef_1e9fb0. */

typedef struct Sub_FUN_002cc8e0 {
    u8 pad000[0x4];
    f32 f;          /* +0x4 */
} Sub_FUN_002cc8e0;

typedef struct Obj_FUN_002cc8e0 {
    s32 g;             /* +0x0 */
    Sub_FUN_002cc8e0 *p;   /* +0x4 */
} Obj_FUN_002cc8e0;

void ScriptSlotStoreFloatRef_2cc8e0(Obj_FUN_002cc8e0 *o, f32 value)
{
    if (o->g == 3) {
        o->p->f = value;
    }
}
