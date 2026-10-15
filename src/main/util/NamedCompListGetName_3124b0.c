#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_003124b0 {
    s32 field;         /* +0x00 */
} Obj_FUN_003124b0;

s32 NamedCompListGetName_3124b0(Obj_FUN_003124b0 *o)
{
    return o->field;
}
