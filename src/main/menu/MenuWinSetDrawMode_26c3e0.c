#include "types.h"

/* Write the s32 at +0x4. */

typedef struct Obj_FUN_0026c3e0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0026c3e0;

void MenuWinSetDrawMode_26c3e0(Obj_FUN_0026c3e0 *o, s32 value)
{
    o->field = value;
}
