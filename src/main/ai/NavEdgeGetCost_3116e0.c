#include "types.h"

/* Read the f32 at +0x8. */

typedef struct Obj_FUN_003116e0 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_003116e0;

f32 NavEdgeGetCost_3116e0(Obj_FUN_003116e0 *o)
{
    return o->field;
}
