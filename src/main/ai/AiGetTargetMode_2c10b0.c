#include "types.h"

/* Read the s32 at +0x288. */

typedef struct Obj_FUN_002c10b0 {
    u8 pad000[0x288];
    s32 field;         /* +0x288 */
} Obj_FUN_002c10b0;

s32 AiGetTargetMode_2c10b0(Obj_FUN_002c10b0 *o)
{
    return o->field;
}
