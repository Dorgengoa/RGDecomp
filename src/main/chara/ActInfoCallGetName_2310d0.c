#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_002310d0 {
    s32 field;         /* +0x00 */
} Obj_FUN_002310d0;

s32 ActInfoCallGetName_2310d0(Obj_FUN_002310d0 *o)
{
    return o->field;
}
