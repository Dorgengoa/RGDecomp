#include "types.h"

/* Read the s32 at +0xB0C. */

typedef struct Obj_FUN_00212240 {
    u8 pad000[0xB0C];
    s32 field;         /* +0xB0C */
} Obj_FUN_00212240;

s32 CharaGetEffectId_212240(Obj_FUN_00212240 *o)
{
    return o->field;
}
