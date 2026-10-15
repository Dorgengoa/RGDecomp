#include "types.h"

/* Write the s32 at +0x100. */

typedef struct Obj_FUN_00256940 {
    u8 pad000[0x100];
    s32 field;         /* +0x100 */
} Obj_FUN_00256940;

void SplinePathSetDuration_256940(Obj_FUN_00256940 *o, s32 value)
{
    o->field = value;
}
