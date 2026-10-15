#include "types.h"

/* Write the s32 at +0x30. */

typedef struct Obj_FUN_0026c260 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_0026c260;

void MenuWinSetAlphaBlend_26c260(Obj_FUN_0026c260 *o, s32 value)
{
    o->field = value;
}
