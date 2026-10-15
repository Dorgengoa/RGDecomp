#include "types.h"

/* Write the s32 at +0x18. */

typedef struct Obj_FUN_00340230 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_00340230;

void CaptionCfgSetTexName_340230(Obj_FUN_00340230 *o, s32 value)
{
    o->field = value;
}
