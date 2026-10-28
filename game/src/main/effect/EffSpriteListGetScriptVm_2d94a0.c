/* rgp:protos */
#define RGP_SELF_EffSpriteListGetScriptVm_2d94a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x1A8. */

typedef struct Obj_FUN_002d94a0 {
    u8 pad000[0x1A8];
    u8 sub[1];         /* +0x1A8 */
} Obj_FUN_002d94a0;

void *EffSpriteListGetScriptVm_2d94a0(Obj_FUN_002d94a0 *o)
{
    return o->sub;
}
