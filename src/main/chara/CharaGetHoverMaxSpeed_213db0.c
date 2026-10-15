#include "types.h"

/* Read the f32 at +0xA64. */

typedef struct Obj_FUN_00213db0 {
    u8 pad000[0xA64];
    f32 field;         /* +0xA64 */
} Obj_FUN_00213db0;

f32 CharaGetHoverMaxSpeed_213db0(Obj_FUN_00213db0 *o)
{
    return o->field;
}
