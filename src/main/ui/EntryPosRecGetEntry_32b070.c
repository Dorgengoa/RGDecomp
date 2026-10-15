#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_0032b070 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_0032b070;

s32 EntryPosRecGetEntry_32b070(Obj_FUN_0032b070 *o)
{
    return o->field;
}
