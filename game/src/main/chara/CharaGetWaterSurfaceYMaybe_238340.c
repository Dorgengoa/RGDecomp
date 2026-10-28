/* rgp:protos */
#define RGP_SELF_CharaGetWaterSurfaceYMaybe_238340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x3F0. */

typedef struct Obj_FUN_00238340 {
    u8 pad000[0x3F0];
    f32 field;         /* +0x3F0 */
} Obj_FUN_00238340;

f32 CharaGetWaterSurfaceYMaybe_238340(Obj_FUN_00238340 *o)
{
    return o->field;
}
