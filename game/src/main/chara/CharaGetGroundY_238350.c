/* rgp:protos */
#define RGP_SELF_CharaGetGroundY_238350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x3EC. */

typedef struct Obj_FUN_00238350 {
    u8 pad000[0x3EC];
    f32 field;         /* +0x3EC */
} Obj_FUN_00238350;

f32 CharaGetGroundY_238350(Obj_FUN_00238350 *o)
{
    return o->field;
}
