/* rgp:protos */
#define RGP_SELF_SurfaceParamGetSlideDecel_23a310 1
#include "port/game_protos.h"
#line 1
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
