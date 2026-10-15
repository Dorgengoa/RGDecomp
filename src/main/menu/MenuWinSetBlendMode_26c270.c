#include "types.h"

/* Write the s32 at +0x2C. */

typedef struct Obj_FUN_0026c270 {
    u8 pad000[0x2C];
    s32 field;         /* +0x2C */
} Obj_FUN_0026c270;

void MenuWinSetBlendMode_26c270(Obj_FUN_0026c270 *o, s32 value)
{
    o->field = value;
}
