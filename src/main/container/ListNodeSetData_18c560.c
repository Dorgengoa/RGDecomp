#include "types.h"

/* Write the s32 at +0x10. */

typedef struct Obj_FUN_0018c560 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_0018c560;

void ListNodeSetData_18c560(Obj_FUN_0018c560 *o, s32 value)
{
    o->field = value;
}
