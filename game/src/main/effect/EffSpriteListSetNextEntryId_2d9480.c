/* rgp:protos */
#define RGP_SELF_EffSpriteListSetNextEntryId_2d9480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x23E. */

typedef struct Obj_FUN_002d9480 {
    u8 pad000[0x23E];
    s16 field;         /* +0x23E */
} Obj_FUN_002d9480;

void EffSpriteListSetNextEntryId_2d9480(Obj_FUN_002d9480 *o, s16 value)
{
    o->field = value;
}
