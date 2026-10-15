#include "types.h"

/* Read the s32 at +0xEC. */

typedef struct Obj_FUN_00336140 {
    u8 pad000[0xEC];
    s32 field;         /* +0xEC */
} Obj_FUN_00336140;

s32 EvObjLiftGetVolumeRec_336140(Obj_FUN_00336140 *o)
{
    return o->field;
}
