#include "types.h"

/* Write the s32 at +0x1A4. */

typedef struct Obj_FUN_00303d80 {
    u8 pad000[0x1A4];
    s32 field;         /* +0x1A4 */
} Obj_FUN_00303d80;

void EvDoorObjSetStateFlagName_303d80(Obj_FUN_00303d80 *o, s32 value)
{
    o->field = value;
}
