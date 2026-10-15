#include "types.h"

/* Read the s32 at +0x30. */

typedef struct Obj_FUN_003238f0 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_003238f0;

s32 EntryGetExploredOffset_3238f0(Obj_FUN_003238f0 *o)
{
    return o->field;
}
