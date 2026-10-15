#include "types.h"

/* Read the s32 at +0x24. */

typedef struct Obj_FUN_002fa7a0 {
    u8 pad000[0x24];
    s32 field;         /* +0x24 */
} Obj_FUN_002fa7a0;

s32 MapNodeMoverGetAreaId_2fa7a0(Obj_FUN_002fa7a0 *o)
{
    return o->field;
}
