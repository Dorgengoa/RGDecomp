#include "types.h"

/* Read the s32 at +0xE0. */

typedef struct Obj_FUN_00372ab0 {
    u8 pad000[0xE0];
    s32 field;         /* +0xE0 */
} Obj_FUN_00372ab0;

s32 ObjTypeMonographGetVolumeRec_372ab0(Obj_FUN_00372ab0 *o)
{
    return o->field;
}
