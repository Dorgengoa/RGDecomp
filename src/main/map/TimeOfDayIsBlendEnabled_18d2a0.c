#include "types.h"

/* Read the s32 at +0x1F0. */

typedef struct Obj_FUN_0018d2a0 {
    u8 pad000[0x1F0];
    s32 field;         /* +0x1F0 */
} Obj_FUN_0018d2a0;

s32 TimeOfDayIsBlendEnabled_18d2a0(Obj_FUN_0018d2a0 *o)
{
    return o->field;
}
