#include "types.h"

/* Read the s32 at +0x1A0. */

typedef struct Obj_FUN_00322510 {
    u8 pad000[0x1A0];
    s32 field;         /* +0x1A0 */
} Obj_FUN_00322510;

s32 MinimapSlotIsActive_322510(Obj_FUN_00322510 *o)
{
    return o->field;
}
