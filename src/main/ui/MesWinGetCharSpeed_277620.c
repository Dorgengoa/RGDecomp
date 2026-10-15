#include "types.h"

/* Read the f32 at +0xB0. */

typedef struct Obj_FUN_00277620 {
    u8 pad000[0xB0];
    f32 field;         /* +0xB0 */
} Obj_FUN_00277620;

f32 MesWinGetCharSpeed_277620(Obj_FUN_00277620 *o)
{
    return o->field;
}
