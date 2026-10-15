#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0018c4f0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0018c4f0;

s32 ListNodeNext_18c4f0(Obj_FUN_0018c4f0 *o)
{
    return o->field;
}
