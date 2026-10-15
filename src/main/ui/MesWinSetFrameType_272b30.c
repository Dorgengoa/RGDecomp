#include "types.h"

/* Write the s16 at +0x86. */

typedef struct Obj_FUN_00272b30 {
    u8 pad000[0x86];
    s16 field;         /* +0x86 */
} Obj_FUN_00272b30;

void MesWinSetFrameType_272b30(Obj_FUN_00272b30 *o, s16 value)
{
    o->field = value;
}
