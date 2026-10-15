#include "types.h"

/* Read the s16 at +0x12. */

typedef struct Obj_FUN_00230950 {
    u8 pad000[0x12];
    s16 field;         /* +0x12 */
} Obj_FUN_00230950;

s16 ActInfoClsnGetLinCount_230950(Obj_FUN_00230950 *o)
{
    return o->field;
}
