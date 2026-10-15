#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_001e7bf0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_001e7bf0;

s32 MapDataGetName_1e7bf0(Obj_FUN_001e7bf0 *o)
{
    return o->field;
}
