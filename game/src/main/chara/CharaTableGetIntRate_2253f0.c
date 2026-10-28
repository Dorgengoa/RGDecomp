/* rgp:protos */
#define RGP_SELF_CharaTableGetIntRate_2253f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x34. */

typedef struct Obj_FUN_002253f0 {
    u8 pad000[0x34];
    f32 field;         /* +0x34 */
} Obj_FUN_002253f0;

f32 CharaTableGetIntRate_2253f0(Obj_FUN_002253f0 *o)
{
    return o->field;
}
