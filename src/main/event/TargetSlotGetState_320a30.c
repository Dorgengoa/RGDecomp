#include "types.h"

/* Read the s32 at +0x34. */

typedef struct Obj_FUN_00320a30 {
    u8 pad000[0x34];
    s32 field;         /* +0x34 */
} Obj_FUN_00320a30;

s32 TargetSlotGetState_320a30(Obj_FUN_00320a30 *o)
{
    return o->field;
}
