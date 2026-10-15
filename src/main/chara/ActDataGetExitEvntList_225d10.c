#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_00225d10 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00225d10;

s32 ActDataGetExitEvntList_225d10(Obj_FUN_00225d10 *o)
{
    return o->field;
}
