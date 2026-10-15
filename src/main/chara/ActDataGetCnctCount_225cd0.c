#include "types.h"

/* Read the s16 at +0x24. */

typedef struct Obj_FUN_00225cd0 {
    u8 pad000[0x24];
    s16 field;         /* +0x24 */
} Obj_FUN_00225cd0;

s16 ActDataGetCnctCount_225cd0(Obj_FUN_00225cd0 *o)
{
    return o->field;
}
