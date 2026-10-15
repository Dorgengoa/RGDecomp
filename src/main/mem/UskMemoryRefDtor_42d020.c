#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_0042d020 {
    s32 field;         /* +0x00 */
} Obj_FUN_0042d020;

void UskMemoryRefDtor_42d020(Obj_FUN_0042d020 *o)
{
    o->field = 0;
}
