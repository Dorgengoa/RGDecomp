/* rgp:protos */
#define RGP_SELF_CharaTableSetIntRate_2253e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x34. */

typedef struct Obj_FUN_002253e0 {
    u8 pad000[0x34];
    f32 field;         /* +0x34 */
} Obj_FUN_002253e0;

void CharaTableSetIntRate_2253e0(Obj_FUN_002253e0 *o, f32 value)
{
    o->field = value;
}
