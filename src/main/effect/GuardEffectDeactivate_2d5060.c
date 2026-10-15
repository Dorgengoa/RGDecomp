#include "types.h"

/* Zero the s32 at +0x334. */

typedef struct Obj_FUN_002d5060 {
    u8 pad000[0x334];
    s32 field;         /* +0x334 */
} Obj_FUN_002d5060;

void GuardEffectDeactivate_2d5060(Obj_FUN_002d5060 *o)
{
    o->field = 0;
}
