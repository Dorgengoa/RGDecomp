#include "types.h"

/* Write the s16 at +0x18. */

typedef struct Obj_FUN_003236a0 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_003236a0;

void EntryListSetCount_3236a0(Obj_FUN_003236a0 *o, s16 value)
{
    o->field = value;
}
