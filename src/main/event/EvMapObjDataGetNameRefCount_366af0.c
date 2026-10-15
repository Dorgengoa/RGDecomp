#include "types.h"

/* Read the s16 at +0x2FA. */

typedef struct Obj_FUN_00366af0 {
    u8 pad000[0x2FA];
    s16 field;         /* +0x2FA */
} Obj_FUN_00366af0;

s16 EvMapObjDataGetNameRefCount_366af0(Obj_FUN_00366af0 *o)
{
    return o->field;
}
