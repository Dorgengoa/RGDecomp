#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_002e5730 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_002e5730;

s32 EventRecGetKey_2e5730(Obj_FUN_002e5730 *o)
{
    return o->field;
}
