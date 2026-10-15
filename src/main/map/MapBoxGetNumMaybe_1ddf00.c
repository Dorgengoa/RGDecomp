#include "types.h"

/* Read the s16 at +0x4C. */

typedef struct Obj_FUN_001ddf00 {
    u8 pad000[0x4C];
    s16 field;         /* +0x4C */
} Obj_FUN_001ddf00;

s16 MapBoxGetNumMaybe_1ddf00(Obj_FUN_001ddf00 *o)
{
    return o->field;
}
