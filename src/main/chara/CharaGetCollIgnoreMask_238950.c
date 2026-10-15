#include "types.h"

/* Read the s16 at +0x40E. */

typedef struct Obj_FUN_00238950 {
    u8 pad000[0x40E];
    s16 field;         /* +0x40E */
} Obj_FUN_00238950;

s16 CharaGetCollIgnoreMask_238950(Obj_FUN_00238950 *o)
{
    return o->field;
}
