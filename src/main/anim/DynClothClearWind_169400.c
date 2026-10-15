#include "types.h"

/* Zero the s32 at +0x120. */

typedef struct Obj_FUN_00169400 {
    u8 pad000[0x120];
    s32 field;         /* +0x120 */
} Obj_FUN_00169400;

void DynClothClearWind_169400(Obj_FUN_00169400 *o)
{
    o->field = 0;
}
