#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0028b220 {
    s32 field;         /* +0x00 */
} Obj_FUN_0028b220;

s32 LoadHandleGetId_28b220(Obj_FUN_0028b220 *o)
{
    return o->field;
}
