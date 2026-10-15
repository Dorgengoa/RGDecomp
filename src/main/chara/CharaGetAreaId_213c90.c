#include "types.h"

/* Read the s32 at +0xA4C. */

typedef struct Obj_FUN_00213c90 {
    u8 pad000[0xA4C];
    s32 field;         /* +0xA4C */
} Obj_FUN_00213c90;

s32 CharaGetAreaId_213c90(Obj_FUN_00213c90 *o)
{
    return o->field;
}
