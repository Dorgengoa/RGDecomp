#include "types.h"

/* Write the f32 at +0x14. */

typedef struct Obj_FUN_003715d0 {
    u8 pad000[0x14];
    f32 field;         /* +0x14 */
} Obj_FUN_003715d0;

void CompassHudSetNeedleAngle_3715d0(Obj_FUN_003715d0 *o, f32 value)
{
    o->field = value;
}
