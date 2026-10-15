#include "types.h"

/* Read the s32 at +0x38. */

typedef struct Obj_FUN_002a02d0 {
    u8 pad000[0x38];
    s32 field;         /* +0x38 */
} Obj_FUN_002a02d0;

s32 MenuGetSelItem_2a02d0(Obj_FUN_002a02d0 *o)
{
    return o->field;
}
