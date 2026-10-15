#include "types.h"

/* Read the s32 at +0x3F4. */

typedef struct Obj_FUN_002386f0 {
    u8 pad000[0x3F4];
    s32 field;         /* +0x3F4 */
} Obj_FUN_002386f0;

s32 CharaGetModelObj_2386f0(Obj_FUN_002386f0 *o)
{
    return o->field;
}
