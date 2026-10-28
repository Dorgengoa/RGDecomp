/* rgp:protos */
#define RGP_SELF_GsPktSetTexFilter_13e3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xE0. */

typedef struct Obj_FUN_0013e3d0 {
    u8 pad000[0xE0];
    s32 field;         /* +0xE0 */
} Obj_FUN_0013e3d0;

void GsPktSetTexFilter_13e3d0(Obj_FUN_0013e3d0 *o, s32 value)
{
    o->field = value;
}
