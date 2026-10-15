#include "types.h"

/* Write the s32 at +0xBC. */

typedef struct Obj_FUN_0026c3d0 {
    u8 pad000[0xBC];
    s32 field;         /* +0xBC */
} Obj_FUN_0026c3d0;

void MenuWinSetDrawLayer_26c3d0(Obj_FUN_0026c3d0 *o, s32 value)
{
    o->field = value;
}
