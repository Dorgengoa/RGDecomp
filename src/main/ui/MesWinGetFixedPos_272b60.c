#include "types.h"

/* Read the s8 at +0x84. */

typedef struct Obj_FUN_00272b60 {
    u8 pad000[0x84];
    s8 field;         /* +0x84 */
} Obj_FUN_00272b60;

s8 MesWinGetFixedPos_272b60(Obj_FUN_00272b60 *o)
{
    return o->field;
}
