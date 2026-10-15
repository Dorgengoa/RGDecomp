#include "types.h"

/* Read the s32 at +0xD0. */

typedef struct Obj_FUN_002f9ce0 {
    u8 pad000[0xD0];
    s32 field;         /* +0xD0 */
} Obj_FUN_002f9ce0;

s32 EvObjGetFlags_2f9ce0(Obj_FUN_002f9ce0 *o)
{
    return o->field;
}
