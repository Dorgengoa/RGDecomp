#include "types.h"

/* Write the s16 at +0x1C. */

typedef struct Obj_FUN_00311950 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_00311950;

void NavNodeSetReachable_311950(Obj_FUN_00311950 *o, s16 value)
{
    o->field = value;
}
