#include "types.h"

/* Read the s16 at +0x10E. */

typedef struct Obj_FUN_00310e70 {
    u8 pad000[0x10E];
    s16 field;         /* +0x10E */
} Obj_FUN_00310e70;

s16 NavGraphGetGoalNodeId_310e70(Obj_FUN_00310e70 *o)
{
    return o->field;
}
