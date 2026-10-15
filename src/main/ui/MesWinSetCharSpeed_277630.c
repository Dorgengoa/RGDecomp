#include "types.h"

/* Write the f32 at +0xB0. */

typedef struct Obj_FUN_00277630 {
    u8 pad000[0xB0];
    f32 field;         /* +0xB0 */
} Obj_FUN_00277630;

void MesWinSetCharSpeed_277630(Obj_FUN_00277630 *o, f32 value)
{
    o->field = value;
}
