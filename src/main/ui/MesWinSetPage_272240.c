#include "types.h"

/* Write the s16 at +0x58. */

typedef struct Obj_FUN_00272240 {
    u8 pad000[0x58];
    s16 field;         /* +0x58 */
} Obj_FUN_00272240;

void MesWinSetPage_272240(Obj_FUN_00272240 *o, s16 value)
{
    o->field = value;
}
