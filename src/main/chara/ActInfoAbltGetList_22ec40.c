#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0022ec40 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0022ec40;

s32 ActInfoAbltGetList_22ec40(Obj_FUN_0022ec40 *o)
{
    return o->field;
}
