#include "types.h"

/* Write the s16 at +0x1C. */

typedef struct Obj_FUN_001d20f0 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_001d20f0;

void SoundSlotSetIndex_1d20f0(Obj_FUN_001d20f0 *o, s16 value)
{
    o->field = value;
}
