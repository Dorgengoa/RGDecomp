#include "types.h"

/* Write the s16 at +0x10. */

typedef struct Obj_FUN_00230940 {
    u8 pad000[0x10];
    s16 field;         /* +0x10 */
} Obj_FUN_00230940;

void ActInfoClsnSetPntCount_230940(Obj_FUN_00230940 *o, s16 value)
{
    o->field = value;
}
