#include "types.h"

/* Read the f32 at +0x9C. */

typedef struct Obj_FUN_00277540 {
    u8 pad000[0x9C];
    f32 field;         /* +0x9C */
} Obj_FUN_00277540;

f32 MesWinGetOpenRate_277540(Obj_FUN_00277540 *o)
{
    return o->field;
}
