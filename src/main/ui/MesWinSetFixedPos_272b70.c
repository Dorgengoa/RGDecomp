#include "types.h"

/* Write the u8 at +0x84. */

typedef struct Obj_FUN_00272b70 {
    u8 pad000[0x84];
    u8 field;         /* +0x84 */
} Obj_FUN_00272b70;

void MesWinSetFixedPos_272b70(Obj_FUN_00272b70 *o, u8 value)
{
    o->field = value;
}
