#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_002e4560 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_002e4560;

s32 EventPathGetFlags_2e4560(Obj_FUN_002e4560 *o)
{
    return o->field;
}
