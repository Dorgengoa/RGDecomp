#include "types.h"

/* Read the s16 at +0xA. */

typedef struct Obj_FUN_001ddbe0 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_001ddbe0;

s16 MapIdIndexGetMinId_1ddbe0(Obj_FUN_001ddbe0 *o)
{
    return o->field;
}
