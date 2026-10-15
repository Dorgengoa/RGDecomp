#include "types.h"

/* Read the f32 at +0xE0. */

typedef struct Obj_FUN_002f93a0 {
    u8 pad000[0xE0];
    f32 field;         /* +0xE0 */
} Obj_FUN_002f93a0;

f32 EvTargetPointObjGetRadius_2f93a0(Obj_FUN_002f93a0 *o)
{
    return o->field;
}
