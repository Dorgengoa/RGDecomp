#include "types.h"

/* Read the f32 at +0x3C. */

typedef struct Obj_FUN_001e7710 {
    u8 pad000[0x3C];
    f32 field;         /* +0x3C */
} Obj_FUN_001e7710;

f32 MapDataGetRotY_1e7710(Obj_FUN_001e7710 *o)
{
    return o->field;
}
