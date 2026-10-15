#include "types.h"

/* Read the f32 at +0x60. */

typedef struct Obj_FUN_0026c230 {
    u8 pad000[0x60];
    f32 field;         /* +0x60 */
} Obj_FUN_0026c230;

f32 MenuWinGetRotZ_26c230(Obj_FUN_0026c230 *o)
{
    return o->field;
}
