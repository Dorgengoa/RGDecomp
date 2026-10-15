#include "types.h"

/* Read the f32 at +0x8. */

typedef struct Obj_FUN_0023a320 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_0023a320;

f32 SurfaceParamGetAccelMaybe_23a320(Obj_FUN_0023a320 *o)
{
    return o->field;
}
