#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_002309a0 {
    s32 field;         /* +0x00 */
} Obj_FUN_002309a0;

s32 ActInfoClsnGetName_2309a0(Obj_FUN_002309a0 *o)
{
    return o->field;
}
