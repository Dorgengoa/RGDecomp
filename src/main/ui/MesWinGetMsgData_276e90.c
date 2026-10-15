#include "types.h"

/* Read the s32 at +0x1DE8. */

typedef struct Obj_FUN_00276e90 {
    u8 pad000[0x1DE8];
    s32 field;         /* +0x1DE8 */
} Obj_FUN_00276e90;

s32 MesWinGetMsgData_276e90(Obj_FUN_00276e90 *o)
{
    return o->field;
}
