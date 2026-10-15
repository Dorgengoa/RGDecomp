#include "types.h"

/* Read the s32 at +0x404. */

typedef struct Obj_FUN_00238560 {
    u8 pad000[0x404];
    s32 field;         /* +0x404 */
} Obj_FUN_00238560;

s32 CharaGetCurMotionName_238560(Obj_FUN_00238560 *o)
{
    return o->field;
}
