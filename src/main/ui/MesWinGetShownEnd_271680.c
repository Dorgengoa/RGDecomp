#include "types.h"

/* Read the s32 at +0xBC. */

typedef struct Obj_FUN_00271680 {
    u8 pad000[0xBC];
    s32 field;         /* +0xBC */
} Obj_FUN_00271680;

s32 MesWinGetShownEnd_271680(Obj_FUN_00271680 *o)
{
    return o->field;
}
