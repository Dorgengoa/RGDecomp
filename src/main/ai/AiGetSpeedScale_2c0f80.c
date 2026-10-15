#include "types.h"

/* Read the f32 at +0x280. */

typedef struct Obj_FUN_002c0f80 {
    u8 pad000[0x280];
    f32 field;         /* +0x280 */
} Obj_FUN_002c0f80;

f32 AiGetSpeedScale_2c0f80(Obj_FUN_002c0f80 *o)
{
    return o->field;
}
