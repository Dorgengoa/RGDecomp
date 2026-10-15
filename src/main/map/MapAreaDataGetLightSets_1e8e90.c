#include "types.h"

/* Read the s32 at +0x16B0. */

typedef struct Obj_FUN_001e8e90 {
    u8 pad000[0x16B0];
    s32 field;         /* +0x16B0 */
} Obj_FUN_001e8e90;

s32 MapAreaDataGetLightSets_1e8e90(Obj_FUN_001e8e90 *o)
{
    return o->field;
}
