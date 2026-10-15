#include "types.h"

/* Zero the s32 at +0x4. */

typedef struct Obj_FUN_00171420 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00171420;

void Vec3VectorClear_171420(Obj_FUN_00171420 *o)
{
    o->field = 0;
}
