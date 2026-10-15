#include "types.h"

/* Read the s32 at +0x100. */

typedef struct Obj_FUN_00310e90 {
    u8 pad000[0x100];
    s32 field;         /* +0x100 */
} Obj_FUN_00310e90;

s32 NavGraphGetId_310e90(Obj_FUN_00310e90 *o)
{
    return o->field;
}
