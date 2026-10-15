#include "types.h"

/* Write the s32 at +0xBC. */

typedef struct Obj_FUN_00271690 {
    u8 pad000[0xBC];
    s32 field;         /* +0xBC */
} Obj_FUN_00271690;

void MesWinSetShownEnd_271690(Obj_FUN_00271690 *o, s32 value)
{
    o->field = value;
}
