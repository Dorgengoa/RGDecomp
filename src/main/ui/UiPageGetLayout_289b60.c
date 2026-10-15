#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_00289b60 {
    s32 field;         /* +0x00 */
} Obj_FUN_00289b60;

s32 UiPageGetLayout_289b60(Obj_FUN_00289b60 *o)
{
    return o->field;
}
