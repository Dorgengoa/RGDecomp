/* rgp:protos */
#define RGP_SELF_EffSpriteListSetTexGroup_2d9460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x26C. */

typedef struct Obj_FUN_002d9460 {
    u8 pad000[0x26C];
    s32 field;         /* +0x26C */
} Obj_FUN_002d9460;

void EffSpriteListSetTexGroup_2d9460(Obj_FUN_002d9460 *o, s32 value)
{
    o->field = value;
}
