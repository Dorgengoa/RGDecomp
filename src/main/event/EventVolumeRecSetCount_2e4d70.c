#include "types.h"

/* Write the s32 at +0x14. */

typedef struct Obj_FUN_002e4d70 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_002e4d70;

void EventVolumeRecSetCount_2e4d70(Obj_FUN_002e4d70 *o, s32 value)
{
    o->field = value;
}
