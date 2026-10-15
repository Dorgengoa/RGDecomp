#include "types.h"

/* Read the s16 at +0xE. */

typedef struct Obj_FUN_002e4550 {
    u8 pad000[0xE];
    s16 field;         /* +0xE */
} Obj_FUN_002e4550;

s16 EventPathGetTotalLength_2e4550(Obj_FUN_002e4550 *o)
{
    return o->field;
}
