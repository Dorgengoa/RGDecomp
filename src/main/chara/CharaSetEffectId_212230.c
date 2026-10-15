#include "types.h"

/* Write the s32 at +0xB0C. */

typedef struct Obj_FUN_00212230 {
    u8 pad000[0xB0C];
    s32 field;         /* +0xB0C */
} Obj_FUN_00212230;

void CharaSetEffectId_212230(Obj_FUN_00212230 *o, s32 value)
{
    o->field = value;
}
