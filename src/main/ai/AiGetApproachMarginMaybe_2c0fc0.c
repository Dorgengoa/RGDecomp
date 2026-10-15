#include "types.h"

/* Read the f32 at +0x270. */

typedef struct Obj_FUN_002c0fc0 {
    u8 pad000[0x270];
    f32 field;         /* +0x270 */
} Obj_FUN_002c0fc0;

f32 AiGetApproachMarginMaybe_2c0fc0(Obj_FUN_002c0fc0 *o)
{
    return o->field;
}
