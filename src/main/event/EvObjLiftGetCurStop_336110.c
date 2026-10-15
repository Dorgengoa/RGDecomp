#include "types.h"

/* Read the s16 at +0x10C. */

typedef struct Obj_FUN_00336110 {
    u8 pad000[0x10C];
    s16 field;         /* +0x10C */
} Obj_FUN_00336110;

s16 EvObjLiftGetCurStop_336110(Obj_FUN_00336110 *o)
{
    return o->field;
}
