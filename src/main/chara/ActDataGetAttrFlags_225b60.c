#include "types.h"

/* Read the s64 at +0x0. */

typedef struct Obj_FUN_00225b60 {
    s64 field;         /* +0x00 */
} Obj_FUN_00225b60;

s64 ActDataGetAttrFlags_225b60(Obj_FUN_00225b60 *o)
{
    return o->field;
}
