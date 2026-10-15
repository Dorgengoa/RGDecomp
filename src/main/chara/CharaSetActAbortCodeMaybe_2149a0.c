#include "types.h"

/* Write the s32 at +0xA1C. */

typedef struct Obj_FUN_002149a0 {
    u8 pad000[0xA1C];
    s32 field;         /* +0xA1C */
} Obj_FUN_002149a0;

void CharaSetActAbortCodeMaybe_2149a0(Obj_FUN_002149a0 *o, s32 value)
{
    o->field = value;
}
