/* rgp:protos */
#define RGP_SELF_ScriptSlotStoreFloatRef_3347d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Only in state 3, forward the value into the sub-object.
   Proven at ScriptSlotStoreFloatRef_1e9fb0. */

typedef struct Sub_FUN_003347d0 {
    u8 pad000[0x4];
    f32 f;          /* +0x4 */
} Sub_FUN_003347d0;

typedef struct Obj_FUN_003347d0 {
    s32 g;             /* +0x0 */
    Sub_FUN_003347d0 *p;   /* +0x4 */
} Obj_FUN_003347d0;

void ScriptSlotStoreFloatRef_3347d0(Obj_FUN_003347d0 *o, f32 value)
{
    if (o->g == 3) {
        o->p->f = value;
    }
}
