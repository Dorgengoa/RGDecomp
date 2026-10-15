#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_001b4aa0 {
    s32 field;         /* +0x00 */
} Obj_FUN_001b4aa0;

void MotionEventListClear_1b4aa0(Obj_FUN_001b4aa0 *o)
{
    o->field = 0;
}
