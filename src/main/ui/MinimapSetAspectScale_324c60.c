#include "types.h"

/* Write the f32 at +0xF8. */

typedef struct Obj_FUN_00324c60 {
    u8 pad000[0xF8];
    f32 field;         /* +0xF8 */
} Obj_FUN_00324c60;

void MinimapSetAspectScale_324c60(Obj_FUN_00324c60 *o, f32 value)
{
    o->field = value;
}
