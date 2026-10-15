#include "types.h"

/* Read the f32 at +0x0. */

typedef struct Obj_FUN_0015f7e0 {
    f32 field;         /* +0x00 */
} Obj_FUN_0015f7e0;

f32 CameraBaseGetFov_15f7e0(Obj_FUN_0015f7e0 *o)
{
    return o->field;
}
