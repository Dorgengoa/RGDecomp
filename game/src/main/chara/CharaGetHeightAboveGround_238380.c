/* rgp:protos */
#define RGP_SELF_CharaGetHeightAboveGround_238380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x3E0. */

typedef struct Obj_FUN_00238380 {
    u8 pad000[0x3E0];
    f32 field;         /* +0x3E0 */
} Obj_FUN_00238380;

f32 CharaGetHeightAboveGround_238380(Obj_FUN_00238380 *o)
{
    return o->field;
}
