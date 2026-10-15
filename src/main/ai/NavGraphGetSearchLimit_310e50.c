#include "types.h"

/* Read the f32 at +0x104. */

typedef struct Obj_FUN_00310e50 {
    u8 pad000[0x104];
    f32 field;         /* +0x104 */
} Obj_FUN_00310e50;

f32 NavGraphGetSearchLimit_310e50(Obj_FUN_00310e50 *o)
{
    return o->field;
}
