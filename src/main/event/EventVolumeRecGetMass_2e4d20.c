#include "types.h"

/* Read the f32 at +0x24. */

typedef struct Obj_FUN_002e4d20 {
    u8 pad000[0x24];
    f32 field;         /* +0x24 */
} Obj_FUN_002e4d20;

f32 EventVolumeRecGetMass_2e4d20(Obj_FUN_002e4d20 *o)
{
    return o->field;
}
