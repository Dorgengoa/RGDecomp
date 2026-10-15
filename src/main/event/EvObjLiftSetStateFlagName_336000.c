#include "types.h"

/* Write the s32 at +0xF4. */

typedef struct Obj_FUN_00336000 {
    u8 pad000[0xF4];
    s32 field;         /* +0xF4 */
} Obj_FUN_00336000;

void EvObjLiftSetStateFlagName_336000(Obj_FUN_00336000 *o, s32 value)
{
    o->field = value;
}
