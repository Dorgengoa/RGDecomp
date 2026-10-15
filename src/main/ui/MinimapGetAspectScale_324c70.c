#include "types.h"

/* Read the f32 at +0xF8. */

typedef struct Obj_FUN_00324c70 {
    u8 pad000[0xF8];
    f32 field;         /* +0xF8 */
} Obj_FUN_00324c70;

f32 MinimapGetAspectScale_324c70(Obj_FUN_00324c70 *o)
{
    return o->field;
}
