#include "types.h"

/* Read the f32 at +0x20. */

typedef struct Obj_FUN_001d2120 {
    u8 pad000[0x20];
    f32 field;         /* +0x20 */
} Obj_FUN_001d2120;

f32 SoundSlotGetVolume_1d2120(Obj_FUN_001d2120 *o)
{
    return o->field;
}
