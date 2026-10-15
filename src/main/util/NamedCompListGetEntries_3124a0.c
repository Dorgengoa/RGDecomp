#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_003124a0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_003124a0;

s32 NamedCompListGetEntries_3124a0(Obj_FUN_003124a0 *o)
{
    return o->field;
}
