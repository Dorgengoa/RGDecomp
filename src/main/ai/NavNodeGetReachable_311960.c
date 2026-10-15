#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_00311960 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_00311960;

s16 NavNodeGetReachable_311960(Obj_FUN_00311960 *o)
{
    return o->field;
}
