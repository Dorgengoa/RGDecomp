#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_00304790 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_00304790;

void EventRefListSetCount_304790(Obj_FUN_00304790 *o, s32 value)
{
    o->field = value;
}
