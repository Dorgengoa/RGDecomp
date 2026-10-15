#include "types.h"

/* Read the s32 at +0x2F4. */

typedef struct Obj_FUN_00366ad0 {
    u8 pad000[0x2F4];
    s32 field;         /* +0x2F4 */
} Obj_FUN_00366ad0;

s32 EvMapObjDataGetNodes_366ad0(Obj_FUN_00366ad0 *o)
{
    return o->field;
}
