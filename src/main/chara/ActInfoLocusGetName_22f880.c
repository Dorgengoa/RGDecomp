#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0022f880 {
    s32 field;         /* +0x00 */
} Obj_FUN_0022f880;

s32 ActInfoLocusGetName_22f880(Obj_FUN_0022f880 *o)
{
    return o->field;
}
