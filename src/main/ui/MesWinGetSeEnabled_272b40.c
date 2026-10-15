#include "types.h"

/* Read the s8 at +0x85. */

typedef struct Obj_FUN_00272b40 {
    u8 pad000[0x85];
    s8 field;         /* +0x85 */
} Obj_FUN_00272b40;

s8 MesWinGetSeEnabled_272b40(Obj_FUN_00272b40 *o)
{
    return o->field;
}
