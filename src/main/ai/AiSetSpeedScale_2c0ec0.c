#include "types.h"

/* Write the f32 at +0x280. */

typedef struct Obj_FUN_002c0ec0 {
    u8 pad000[0x280];
    f32 field;         /* +0x280 */
} Obj_FUN_002c0ec0;

void AiSetSpeedScale_2c0ec0(Obj_FUN_002c0ec0 *o, f32 value)
{
    o->field = value;
}
