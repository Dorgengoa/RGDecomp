#include "types.h"

/* Read the f32 at +0x8. */

typedef struct Obj_FUN_00223cc0 {
    u8 pad000[0x8];
    f32 field;         /* +0x8 */
} Obj_FUN_00223cc0;

f32 ActCfgTableGetJumpHeightMaybe_223cc0(Obj_FUN_00223cc0 *o)
{
    return o->field;
}
