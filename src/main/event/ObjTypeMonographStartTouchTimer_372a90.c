#include "types.h"

/* Zero the s32 at +0x104. */

typedef struct Obj_FUN_00372a90 {
    u8 pad000[0x104];
    s32 field;         /* +0x104 */
} Obj_FUN_00372a90;

void ObjTypeMonographStartTouchTimer_372a90(Obj_FUN_00372a90 *o)
{
    o->field = 0;
}
