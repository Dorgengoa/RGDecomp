#include "types.h"

/* Read the s32 at +0x110. */

typedef struct Obj_FUN_00338040 {
    u8 pad000[0x110];
    s32 field;         /* +0x110 */
} Obj_FUN_00338040;

s32 ObjTypeVehicleGetTargetPairs_338040(Obj_FUN_00338040 *o)
{
    return o->field;
}
