#include "types.h"

/* Read the s32 at +0x1C24. */

typedef struct Obj_FUN_00271b50 {
    u8 pad000[0x1C24];
    s32 field;         /* +0x1C24 */
} Obj_FUN_00271b50;

s32 MesWinGetChoiceIndex_271b50(Obj_FUN_00271b50 *o)
{
    return o->field;
}
