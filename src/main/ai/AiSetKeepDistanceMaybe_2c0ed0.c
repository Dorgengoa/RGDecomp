#include "types.h"

/* Write the f32 at +0x27C. */

typedef struct Obj_FUN_002c0ed0 {
    u8 pad000[0x27C];
    f32 field;         /* +0x27C */
} Obj_FUN_002c0ed0;

void AiSetKeepDistanceMaybe_2c0ed0(Obj_FUN_002c0ed0 *o, f32 value)
{
    o->field = value;
}
