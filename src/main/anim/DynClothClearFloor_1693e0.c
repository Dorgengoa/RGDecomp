#include "types.h"

/* Zero the s32 at +0x148. */

typedef struct Obj_FUN_001693e0 {
    u8 pad000[0x148];
    s32 field;         /* +0x148 */
} Obj_FUN_001693e0;

void DynClothClearFloor_1693e0(Obj_FUN_001693e0 *o)
{
    o->field = 0;
}
