#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_003047b0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_003047b0;

s32 EventRefListGetRefs_3047b0(Obj_FUN_003047b0 *o)
{
    return o->field;
}
