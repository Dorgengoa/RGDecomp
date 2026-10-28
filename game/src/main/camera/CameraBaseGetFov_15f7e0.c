/* rgp:protos */
#define RGP_SELF_CameraBaseGetFov_15f7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x0. */

typedef struct Obj_FUN_0015f7e0 {
    f32 field;         /* +0x00 */
} Obj_FUN_0015f7e0;

f32 CameraBaseGetFov_15f7e0(Obj_FUN_0015f7e0 *o)
{
    return o->field;
}
