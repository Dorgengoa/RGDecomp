#include "types.h"

/* Read the s16 at +0x130. */

typedef struct Obj_FUN_003380a0 {
    u8 pad000[0x130];
    s16 field;         /* +0x130 */
} Obj_FUN_003380a0;

s16 ObjTypeVehicleGetPlayState_3380a0(Obj_FUN_003380a0 *o)
{
    return o->field;
}
