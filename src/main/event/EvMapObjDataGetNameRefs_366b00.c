#include "types.h"

/* Read the s32 at +0x2F0. */

typedef struct Obj_FUN_00366b00 {
    u8 pad000[0x2F0];
    s32 field;         /* +0x2F0 */
} Obj_FUN_00366b00;

s32 EvMapObjDataGetNameRefs_366b00(Obj_FUN_00366b00 *o)
{
    return o->field;
}
