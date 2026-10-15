#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_00209d80 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00209d80;

s32 DebugMenuWidgetGetChildArray_209d80(Obj_FUN_00209d80 *o)
{
    return o->field;
}
