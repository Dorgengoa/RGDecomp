#include "types.h"

/* Read the s32 at +0x80. */

typedef struct Obj_FUN_001dce70 {
    u8 pad000[0x80];
    s32 field;         /* +0x80 */
} Obj_FUN_001dce70;

s32 MapAreaGetFileStem_1dce70(Obj_FUN_001dce70 *o)
{
    return o->field;
}
