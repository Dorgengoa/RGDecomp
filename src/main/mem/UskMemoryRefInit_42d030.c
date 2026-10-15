#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_0042d030 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042d030;

void UskMemoryRefInit_42d030(Obj_FUN_0042d030 *o)
{
    o->field = 0;
}
