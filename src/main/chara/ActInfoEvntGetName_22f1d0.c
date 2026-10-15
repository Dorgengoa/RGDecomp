#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0022f1d0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0022f1d0;

s32 ActInfoEvntGetName_22f1d0(Obj_FUN_0022f1d0 *o)
{
    return o->field;
}
