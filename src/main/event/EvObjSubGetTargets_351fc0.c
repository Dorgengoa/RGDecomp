#include "types.h"

/* Read the s32 at +0xE8. */

typedef struct Obj_FUN_00351fc0 {
    u8 pad000[0xE8];
    s32 field;         /* +0xE8 */
} Obj_FUN_00351fc0;

s32 EvObjSubGetTargets_351fc0(Obj_FUN_00351fc0 *o)
{
    return o->field;
}
