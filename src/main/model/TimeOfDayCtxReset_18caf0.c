#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_0018caf0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0018caf0;

void TimeOfDayCtxReset_18caf0(Obj_FUN_0018caf0 *o)
{
    o->field = 0;
}
