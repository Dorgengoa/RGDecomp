#include "types.h"

/* Write the s16 at +0x20. */

typedef struct Obj_FUN_00225cc0 {
    u8 pad000[0x20];
    s16 field;         /* +0x20 */
} Obj_FUN_00225cc0;

void ActDataSetEvntCount_225cc0(Obj_FUN_00225cc0 *o, s16 value)
{
    o->field = value;
}
