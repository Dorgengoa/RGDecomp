#include "types.h"

/* Write the s32 at +0xF4. */

typedef struct Obj_FUN_0018b5b0 {
    u8 pad000[0xF4];
    s32 field;         /* +0xF4 */
} Obj_FUN_0018b5b0;

void CollFrameSetShape_18b5b0(Obj_FUN_0018b5b0 *o, s32 value)
{
    o->field = value;
}
