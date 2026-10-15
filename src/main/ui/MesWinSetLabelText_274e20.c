#include "types.h"

/* Write the s32 at +0x1950. */

typedef struct Obj_FUN_00274e20 {
    u8 pad000[0x1950];
    s32 field;         /* +0x1950 */
} Obj_FUN_00274e20;

void MesWinSetLabelText_274e20(Obj_FUN_00274e20 *o, s32 value)
{
    o->field = value;
}
