#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_00311700 {
    s16 field;         /* +0x00 */
} Obj_FUN_00311700;

s16 NavEdgeGetNodeA_311700(Obj_FUN_00311700 *o)
{
    return o->field;
}
