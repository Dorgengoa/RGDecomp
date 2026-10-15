#include "types.h"

/* Read the s32 at +0x428. */

typedef struct Obj_FUN_00214cd0 {
    u8 pad000[0x428];
    s32 field;         /* +0x428 */
} Obj_FUN_00214cd0;

s32 CharaGetActionTable_214cd0(Obj_FUN_00214cd0 *o)
{
    return o->field;
}
