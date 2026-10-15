#include "types.h"

/* Write the f32 at +0x9C. */

typedef struct Obj_FUN_00277550 {
    u8 pad000[0x9C];
    f32 field;         /* +0x9C */
} Obj_FUN_00277550;

void MesWinSetOpenRate_277550(Obj_FUN_00277550 *o, f32 value)
{
    o->field = value;
}
