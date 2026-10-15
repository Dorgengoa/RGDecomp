#include "types.h"

/* Read the s32 at +0x20. */

typedef struct Obj_FUN_002fa7b0 {
    u8 pad000[0x20];
    s32 field;         /* +0x20 */
} Obj_FUN_002fa7b0;

s32 MapNodeMoverGetId_2fa7b0(Obj_FUN_002fa7b0 *o)
{
    return o->field;
}
