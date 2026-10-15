#include "types.h"

/* Read the s32 at +0xA0. */

typedef struct Obj_FUN_001e5a40 {
    u8 pad000[0xA0];
    s32 field;         /* +0xA0 */
} Obj_FUN_001e5a40;

s32 MapIdListCount_1e5a40(Obj_FUN_001e5a40 *o)
{
    return o->field;
}
