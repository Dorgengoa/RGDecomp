#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_002a4e30 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_002a4e30;

s32 MenuGetMode_2a4e30(Obj_FUN_002a4e30 *o)
{
    return o->field;
}
