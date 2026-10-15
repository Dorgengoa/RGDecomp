#include "types.h"

/* Read the s16 at +0x1A. */

typedef struct Obj_FUN_00311930 {
    u8 pad000[0x1A];
    s16 field;         /* +0x1A */
} Obj_FUN_00311930;

s16 NavNodeGetEdgeCount_311930(Obj_FUN_00311930 *o)
{
    return o->field;
}
