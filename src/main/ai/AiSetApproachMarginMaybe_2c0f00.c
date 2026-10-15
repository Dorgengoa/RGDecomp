#include "types.h"

/* Write the f32 at +0x270. */

typedef struct Obj_FUN_002c0f00 {
    u8 pad000[0x270];
    f32 field;         /* +0x270 */
} Obj_FUN_002c0f00;

void AiSetApproachMarginMaybe_2c0f00(Obj_FUN_002c0f00 *o, f32 value)
{
    o->field = value;
}
