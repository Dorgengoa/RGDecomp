#include "types.h"

/* Write the f32 at +0x104. */

typedef struct Obj_FUN_00310da0 {
    u8 pad000[0x104];
    f32 field;         /* +0x104 */
} Obj_FUN_00310da0;

void NavGraphSetSearchLimit_310da0(Obj_FUN_00310da0 *o, f32 value)
{
    o->field = value;
}
