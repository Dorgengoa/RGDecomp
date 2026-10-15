#include "types.h"

/* Read the s32 at +0x420. */

typedef struct Obj_FUN_00214a90 {
    u8 pad000[0x420];
    s32 field;         /* +0x420 */
} Obj_FUN_00214a90;

s32 CharaGetHeapBlock_214a90(Obj_FUN_00214a90 *o)
{
    return o->field;
}
