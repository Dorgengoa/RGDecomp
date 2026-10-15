#include "types.h"

/* Read the s32 at +0x20. */

typedef struct Obj_FUN_00226960 {
    u8 pad000[0x20];
    s32 field;         /* +0x20 */
} Obj_FUN_00226960;

s32 CharaTableDataGetTimeCnctList_226960(Obj_FUN_00226960 *o)
{
    return o->field;
}
