#include "types.h"

/* Write the s32 at +0x0. */

typedef struct Obj_FUN_0042cff0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042cff0;

void UskMemoryRefSet_42cff0(Obj_FUN_0042cff0 *o, s32 value)
{
    o->field = value;
}
