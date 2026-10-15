#include "types.h"

/* Write the f32 at +0x32C. */

typedef struct Obj_FUN_002d54b0 {
    u8 pad000[0x32C];
    f32 field;         /* +0x32C */
} Obj_FUN_002d54b0;

void GuardEffectSetSpeedScale_2d54b0(Obj_FUN_002d54b0 *o, f32 value)
{
    o->field = value;
}
