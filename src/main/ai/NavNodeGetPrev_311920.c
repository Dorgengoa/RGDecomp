#include "types.h"

/* Read the s16 at +0x1E. */

typedef struct Obj_FUN_00311920 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_00311920;

s16 NavNodeGetPrev_311920(Obj_FUN_00311920 *o)
{
    return o->field;
}
