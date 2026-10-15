#include "types.h"

/* Read the s16 at +0x10. */

typedef struct Obj_FUN_00230960 {
    u8 pad000[0x10];
    s16 field;         /* +0x10 */
} Obj_FUN_00230960;

s16 ActInfoClsnGetPntCount_230960(Obj_FUN_00230960 *o)
{
    return o->field;
}
