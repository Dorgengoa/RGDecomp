#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_0022eef0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0022eef0;

s32 ActInfoWepActGetList_22eef0(Obj_FUN_0022eef0 *o)
{
    return o->field;
}
