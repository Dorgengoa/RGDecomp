#include "types.h"

/* Read the s32 at +0xE4. */

typedef struct Obj_FUN_00336030 {
    u8 pad000[0xE4];
    s32 field;         /* +0xE4 */
} Obj_FUN_00336030;

s32 EvObjLiftGetTargetSets_336030(Obj_FUN_00336030 *o)
{
    return o->field;
}
