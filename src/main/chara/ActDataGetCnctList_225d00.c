#include "types.h"

/* Read the s32 at +0x1C. */

typedef struct Obj_FUN_00225d00 {
    u8 pad000[0x1C];
    s32 field;         /* +0x1C */
} Obj_FUN_00225d00;

s32 ActDataGetCnctList_225d00(Obj_FUN_00225d00 *o)
{
    return o->field;
}
