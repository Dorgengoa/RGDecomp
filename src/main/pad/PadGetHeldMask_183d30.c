#include "types.h"

/* Return m4 only while m24C is clear.  Spelled `!= 0` so retail's beql makes
   the VALUE the branch target and the 0 the fall-through -- the recorded
   branch-layout rule from SlotGetInt_15f720. */

typedef struct Obj_FUN_00183d30 {
    u8 pad000[0x4];
    s32 m4;            /* +0x04 */
    u8 pad008[0x244];
    s32 m24C;          /* +0x24C */
} Obj_FUN_00183d30;

s32 PadGetHeldMask_183d30(Obj_FUN_00183d30 *o)
{
    if (o->m24C != 0) {
        return 0;
    }
    return o->m4;
}
