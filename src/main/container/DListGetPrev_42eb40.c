#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0042eb40 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042eb40;

s32 DListGetPrev_42eb40(Obj_FUN_0042eb40 *o)
{
    return o->field;
}
