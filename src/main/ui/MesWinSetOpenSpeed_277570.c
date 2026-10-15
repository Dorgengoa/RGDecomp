#include "types.h"

/* Write the f32 at +0x98. */

typedef struct Obj_FUN_00277570 {
    u8 pad000[0x98];
    f32 field;         /* +0x98 */
} Obj_FUN_00277570;

void MesWinSetOpenSpeed_277570(Obj_FUN_00277570 *o, f32 value)
{
    o->field = value;
}
