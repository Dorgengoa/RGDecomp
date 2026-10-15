#include "types.h"

/* Write the s16 at +0x114. */

typedef struct Obj_FUN_00338020 {
    u8 pad000[0x114];
    s16 field;         /* +0x114 */
} Obj_FUN_00338020;

void ObjTypeVehicleSetTargetPairCount_338020(Obj_FUN_00338020 *o, s16 value)
{
    o->field = value;
}
