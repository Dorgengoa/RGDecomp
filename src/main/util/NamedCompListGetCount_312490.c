#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_00312490 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00312490;

s32 NamedCompListGetCount_312490(Obj_FUN_00312490 *o)
{
    return o->field;
}
