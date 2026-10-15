#include "types.h"

/* Read the s16 at +0x22. */

typedef struct Obj_FUN_00225ce0 {
    u8 pad000[0x22];
    s16 field;         /* +0x22 */
} Obj_FUN_00225ce0;

s16 ActDataGetExitEvntCount_225ce0(Obj_FUN_00225ce0 *o)
{
    return o->field;
}
