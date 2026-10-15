#include "types.h"

/* Read the s16 at +0xC. */

typedef struct Obj_FUN_00311720 {
    u8 pad000[0xC];
    s16 field;         /* +0xC */
} Obj_FUN_00311720;

s16 NavEdgeGetId_311720(Obj_FUN_00311720 *o)
{
    return o->field;
}
