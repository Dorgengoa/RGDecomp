#include "types.h"

/* Read the s32 at +0x11C. */

typedef struct Obj_FUN_003380b0 {
    u8 pad000[0x11C];
    s32 field;         /* +0x11C */
} Obj_FUN_003380b0;

s32 ObjTypeVehicleGetPathRec_3380b0(Obj_FUN_003380b0 *o)
{
    return o->field;
}
