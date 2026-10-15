#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_002a4e10 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_002a4e10;

s32 MenuGetSelMode_2a4e10(Obj_FUN_002a4e10 *o)
{
    return o->field;
}
