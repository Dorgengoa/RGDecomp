#include "types.h"

/* Write the s32 at +0x1DE8. */

typedef struct Obj_FUN_00276ea0 {
    u8 pad000[0x1DE8];
    s32 field;         /* +0x1DE8 */
} Obj_FUN_00276ea0;

void MesWinSetMsgData_276ea0(Obj_FUN_00276ea0 *o, s32 value)
{
    o->field = value;
}
