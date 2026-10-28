/* rgp:protos */
#define RGP_SELF_EffSpriteListSetCurEntryId_2d9470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x23C. */

typedef struct Obj_FUN_002d9470 {
    u8 pad000[0x23C];
    s16 field;         /* +0x23C */
} Obj_FUN_002d9470;

void EffSpriteListSetCurEntryId_2d9470(Obj_FUN_002d9470 *o, s16 value)
{
    o->field = value;
}
