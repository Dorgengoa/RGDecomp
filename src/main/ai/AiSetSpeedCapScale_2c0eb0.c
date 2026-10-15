#include "types.h"

/* Write the f32 at +0x284. */

typedef struct Obj_FUN_002c0eb0 {
    u8 pad000[0x284];
    f32 field;         /* +0x284 */
} Obj_FUN_002c0eb0;

void AiSetSpeedCapScale_2c0eb0(Obj_FUN_002c0eb0 *o, f32 value)
{
    o->field = value;
}
