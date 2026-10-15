#include "types.h"

/* Write the s32 at +0x1938. */

typedef struct Obj_FUN_00272ac0 {
    u8 pad000[0x1938];
    s32 field;         /* +0x1938 */
} Obj_FUN_00272ac0;

void MesWinSetPenY_272ac0(Obj_FUN_00272ac0 *o, s32 value)
{
    o->field = value;
}
