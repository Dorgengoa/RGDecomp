#include "types.h"

/* Write the s16 at +0x12. */

typedef struct Obj_FUN_00230930 {
    u8 pad000[0x12];
    s16 field;         /* +0x12 */
} Obj_FUN_00230930;

void ActInfoClsnSetLinCount_230930(Obj_FUN_00230930 *o, s16 value)
{
    o->field = value;
}
