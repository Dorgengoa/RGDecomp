#include "types.h"

/* Read the s16 at +0x20. */

typedef struct Obj_FUN_00225cf0 {
    u8 pad000[0x20];
    s16 field;         /* +0x20 */
} Obj_FUN_00225cf0;

s16 ActDataGetEvntCount_225cf0(Obj_FUN_00225cf0 *o)
{
    return o->field;
}
