#include "types.h"

/* Read the f32 at +0xC. */

typedef struct Obj_FUN_0023a310 {
    u8 pad000[0xC];
    f32 field;         /* +0xC */
} Obj_FUN_0023a310;

f32 SurfaceParamGetSlideDecel_23a310(Obj_FUN_0023a310 *o)
{
    return o->field;
}
