#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_00225d20 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_00225d20;

s32 ActDataGetEvntList_225d20(Obj_FUN_00225d20 *o)
{
    return o->field;
}
