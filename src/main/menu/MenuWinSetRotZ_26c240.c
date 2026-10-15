#include "types.h"

/* Write the f32 at +0x60. */

typedef struct Obj_FUN_0026c240 {
    u8 pad000[0x60];
    f32 field;         /* +0x60 */
} Obj_FUN_0026c240;

void MenuWinSetRotZ_26c240(Obj_FUN_0026c240 *o, f32 value)
{
    o->field = value;
}
