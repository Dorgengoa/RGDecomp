#include "types.h"

/* Write the f32 at +0x10. */

typedef struct Obj_FUN_003715e0 {
    u8 pad000[0x10];
    f32 field;         /* +0x10 */
} Obj_FUN_003715e0;

void CompassHudSetDialAngle_3715e0(Obj_FUN_003715e0 *o, f32 value)
{
    o->field = value;
}
